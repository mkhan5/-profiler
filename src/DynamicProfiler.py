from SourceAST import SourceAST
from FileManagementClass import FileManagement
from pycparser import c_ast, c_parser
import re
import os
import json
import csv

# TODO:
# 1. Add comments
# 2. change Print format to look like JSON format
# 3. Try to add funcCall name to the JSON Format
# 4. Add funcnality to save old headers which can used while compiling, if fake_headers cannot be used -DONE
# 5. Add header file match using regex in SourceCodeClass : (^\s*\#\s*include\s*<([^<>]+)>)|(^\s*\#\s*include\s*"([^"]+)")

class DynamicProfiler:
    def __init__(self, conffile):
        self.filemngr = FileManagement(conffile)

        self.filename = self.filemngr.source_file
        self.platform = self.filemngr.platform

        ast = self.filemngr.getAST()
        self.source = SourceAST(ast)
        self.functions = self.source.functions
        self.output_file= ""
        self.filemngr.compile_command = self.filemngr.compile_command + " -lrt"

    def insert_instrumentation_code(self):
        '''Insert instrumentation code around each block in filename

        :param filename:
        :return:
        '''
        self.filemngr.appendHeaders(["#include<time.h>","\n"])

        ast = self.source.ast

        for i in range(0, len(ast.ext)):
            # Add profiling code related declarations before each function
            self.initProfilingCode("FuncDef","","","")
            if type(ast.ext[i]) == c_ast.FuncDef:
                block_ctr = 0
                for block in self.init_code:
                    ast.ext[i].body.block_items.insert(block_ctr, block)
                    block_ctr += 1

                # Add profiling code related declarations before and after
                # each For and FuncCall block
                total_blocks = len(ast.ext[i].body.block_items)
                ctr = 0
                for block_ctr in range(0, total_blocks):
                    actual_ctr = block_ctr + ctr
                    block_type = type(ast.ext[i].body.block_items[actual_ctr])
                    in_func = ast.ext[i].decl.name
                    if block_type is c_ast.For or block_type is c_ast.FuncCall:
                        func_name = ""
                        if block_type is c_ast.FuncCall:
                            # ignore simple function calls
                            func_name = ast.ext[i].body.block_items[actual_ctr].name.name
                            if func_name == "printf" or func_name == "scanf" or func_name == "fprintf" \
                                    or func_name == "free" or func_name == "malloc":
                                continue
                        self.initProfilingCode(block_type, ctr, in_func, func_name)
                        ast.ext[i].body.block_items.insert(actual_ctr, self.block_start)
                        ctr += 1

                        actual_ctr = block_ctr + ctr
                        for x in range(0, len(self.block_end)):
                            ast.ext[i].body.block_items.insert(actual_ctr+x+1, self.block_end[x])
                            ctr += 1

                        actual_ctr = block_ctr + ctr


        for i in range(0, len(ast.ext)):
            # Add profiling code related declarations before each function
            self.initProfilingCode("FuncDef","","","main")
            if type(ast.ext[i]) == c_ast.FuncDef:

                if ast.ext[i].decl.name == "main":

                    print "I was found here"
                    main_ctr = len(ast.ext[i].body.block_items)
                    print main_ctr
                    for x in range(0, len(self.main_end)):
                            ast.ext[i].body.block_items.insert((main_ctr-1)+x, self.main_end[x])

                    ast.ext[i].body.block_items.insert(0, self.main_start)

                    block_ctr = 0
                    for block in self.init_main_code:
                        ast.ext[i].body.block_items.insert(block_ctr, block)
                        block_ctr += 1



        output_file, file_extension = os.path.splitext(self.filename)
        output_file = output_file+"_prof"+file_extension
        self.output_file = output_file
        self.filemngr.writeASTToFile(output_file, ast)

    def exec_profiler(self):
        output, status = self.filemngr.compileAndExecuteCode(self.output_file)
        return output,status

    def analyze_results(self):
        '''Analyze results from Tulsi.prof

        :return:
        '''
        pass

    def sort_by_time(self,d):
        '''a helper function for sorting'''

        js2 = """[
                    {"In_Function":"init_array","Block_Type":"For","Block_No":"0","Function_Name":"","Time":"0.0000440610"},
                    {"In_Function":"init_array","Block_Type":"For","Block_No":"4","Function_Name":"","Time":"0.1706538520"},
                    {"In_Function":"main","Block_Type":"FuncCall","Block_No":"0","Function_Name":"init_array","Time":"0.1707323500"},
                    {"In_Function":"kernel_atax","Block_Type":"For","Block_No":"0","Function_Name":"","Time":"0.0000175760"},
                    {"In_Function":"kernel_atax","Block_Type":"For","Block_No":"4","Function_Name":"","Time":"0.1267969000"},
                    {"In_Function":"main","Block_Type":"FuncCall","Block_No":"4","Function_Name":"kernel_atax","Time":"0.1268231100"}
                    ]

                    """
        js = """[
         {"In_Function": "init_array", "Block_Type": "For", "Block_No": "0", "Function_Name": "", "Time": "0.0001084660"},
        {"In_Function": "init_array", "Block_Type": "For", "Block_No": "4", "Function_Name": "", "Time": "0.1805580550"},
        {"In_Function": "main", "Block_Type": "FuncCall", "Block_No": "0", "Function_Name": "init_array", "Time": "0.1808280340"},
        {"In_Function": "kernel_atax", "Block_Type": "For", "Block_No": "0", "Function_Name": "", "Time": "0.0000231690"},
        {"In_Function": "kernel_atax", "Block_Type": "For", "Block_No": "4", "Function_Name": "","Time": "0.0000182860"},
        {"In_Function": "kernel_atax", "Block_Type": "FuncCall", "Block_No": "8", "Function_Name": "cblas_dgemv","Time": "0.0813515750"},
        {"In_Function": "kernel_atax", "Block_Type": "FuncCall", "Block_No": "12", "Function_Name": "cblas_dgemv", "Time": "0.0125196280"},
        {"In_Function": "main", "Block_Type": "FuncCall", "Block_No": "4", "Function_Name": "kernel_atax","Time": "0.2107533820"}
            ]
                    """
        return d['Time']

    def generate_report(self,js):
        '''Generate results of the profiler as a meaningful report and recommendations'''

        js = js.strip()
        js = "["+js.replace("\n",",")+"]"
        ud = json.loads(js)
        sorted_list = sorted(ud, key=lambda item: float(item["Time"]), reverse=True)
        # sorted_list = sorted(js, key=self.sort_by_time)
        # sorted_list = sorted(js, key=lambda k: (int(k['score']), -int(k["score"])))

        total_time = sorted_list[0].values()[0]
        percentage = []
        speedup = []
        n = 4 # no  of cores
        for i in range(1,len(sorted_list)):
            print i
            print sorted_list[i].values()[0]
            temp = float(sorted_list[i].values()[0])/float(total_time)
            percentage.append(str(temp*100))
            spdup = n/(1+((n-1)*(1-temp)))
            speedup.append(spdup)


        info_speedup_list = sorted_list


        for i in range(0,len(sorted_list)):
            print i
            if i == 0 :
                info_speedup_list[i]["Coverage"] = "100"
                info_speedup_list[i]["Speedup (if parallelized)"] = "Nil"
            else:
                info_speedup_list[i]["Coverage"] = percentage[i-1]
                info_speedup_list[i]["Speedup (if parallelized)"] = speedup[i-1]




        print info_speedup_list
        prev_dir = os.getcwd()
        os.chdir(self.filemngr.working_dir)
        fp = open(self.output_file+".csv",'w+')
        output = csv.writer(fp)
        output.writerow(info_speedup_list[0].keys())  # header row

        for row in info_speedup_list:
            output.writerow(row.values())
        os.chdir(prev_dir)

    def getProfileData(self):
        '''Generate results of the profiler as a meaningful report and recommendations

        :return:
        '''
        pass

    def initProfilingCode(self, block_type,ctr, in_function,func_name):
        text = r"""
                    typedef int clock_t;

                    func()
                    {
                        struct timespec start;
                        struct timespec end;
                        double cpu_time_used;

                        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
                        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                        cpu_time_used = ((double)end.tv_sec + 1.0e-9*end.tv_nsec) - ((double)start.tv_sec + 1.0e-9*start.tv_nsec);

                        printf("{\"In_Function\":\"_IN_FUNCTION\",\"Block_Type\":\"_BLOCK_TYPE\",\"Block_No\":\"_BLOCK_NO\",\"Function_Name\":\"_FUNC_NAME\",\"Time\":\"%.10f\"}\n", cpu_time_used);
                    }
        """

        main_text = r"""
                    typedef int clock_t;

                    func()
                    {
                        struct timespec mstart;
                        struct timespec mend;
                        double mcpu_time_used;

                        clock_gettime(CLOCK_MONOTONIC_RAW, &mstart);
                        clock_gettime(CLOCK_MONOTONIC_RAW, &mend);
                        mcpu_time_used = ((double)mend.tv_sec + 1.0e-9*mend.tv_nsec) - ((double)mstart.tv_sec + 1.0e-9*mstart.tv_nsec);

                        printf("{\"In_Function\":\"_IN_FUNCTION\",\"Block_Type\":\"_BLOCK_TYPE\",\"Block_No\":\"_BLOCK_NO\",\"Function_Name\":\"_FUNC_NAME\",\"Time\":\"%.10f\"}\n", mcpu_time_used);
                    }
        """
        if block_type is c_ast.FuncCall:
            block_type = "FuncCall"
        elif block_type is c_ast.For:
            block_type = "For"

        text = re.sub("_BLOCK_TYPE", block_type, text)
        text = re.sub("_BLOCK_NO", str(ctr), text)
        text = re.sub("_IN_FUNCTION", in_function, text)
        text = re.sub("_FUNC_NAME", func_name, text)
        parser = c_parser.CParser()
        ast = parser.parse(text, filename='<none>')
        self.init_code = []

        for x in range(0, 3):
            self.init_code.append(ast.ext[1].body.block_items[x])

        self.block_start = ast.ext[1].body.block_items[3]

        self.block_end = []
        for x in range(4, 7):
            self.block_end.append(ast.ext[1].body.block_items[x])

        """ For inserting variables and clock in main function at start and at end only """
        main_text = re.sub("_BLOCK_TYPE", block_type, main_text)
        main_text = re.sub("_BLOCK_NO", str(ctr), main_text)
        main_text = re.sub("_IN_FUNCTION", in_function, main_text)
        main_text = re.sub("_FUNC_NAME", func_name, main_text)
        parser = c_parser.CParser()
        ast = parser.parse(main_text, filename='<none>')
        self.init_main_code = []

        for x in range(0, 3):
            self.init_main_code.append(ast.ext[1].body.block_items[x])

        self.main_start = ast.ext[1].body.block_items[3]

        self.main_end = []
        for x in range(4, 7):
            self.main_end.append(ast.ext[1].body.block_items[x])

if __name__ == '__main__':
    profiler = DynamicProfiler("../input/polybench_gemv.conf")
    profiler.insert_instrumentation_code()
    output, stat = profiler.exec_profiler()
    #print stat
    if stat == 0:
        profiler.generate_report(output)

