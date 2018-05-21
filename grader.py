#!/usr/bin/python

import os
import json # for parsing json
import itertools # for flattening arrays
import subprocess # for running shell commands
import shutil # for copying files
import operator # for operator.gt and operator.lt
from threading import Timer # for timeout
import argparse

class CppGrader:

    base_dir = ""
    input_file_dir = "input_files"
    candidate_dir = "candidate"
    settings_file = "settings.json";

    def __init__(self, base_dir, settings_file="settings.json"):
        self.base_dir = base_dir
        self.settings_file = settings_file

    def populateCandidateDir(self, target_path, verbose):
        if (not os.path.os.path.exists(target_path)):
            self.__print("\t" + tar_path + " does not exist, could not populate candidate.", verbose)
            return False

        extension = os.path.splitext(target_path)[1]
        if(extension == ".tgz"): # code for .tzg files
            target_name = os.path.basename(target_path)
            candidate_dir = os.path.join(self.base_dir, self.candidate_dir)
            
            try:
                dst_path = os.path.join(candidate_dir, target_name)
                shutil.copyfile(target_path, dst_path)
            except:
                self.__print("\t" + target_path + " failed to copy tar file " + target_name + " to " + dst_path, verbose)
                return False
            
            self.__shellcmd("tar -xzf \"" + target_name + "\"", candidate_dir)
            self.__print("\tcopied and extracted " + target_name + " to " + dst_path, verbose)
            return True
        else:
            return False


    def runCandidate(self, verbose):
    # Execute programs in candidate folder and check output
    
        self.__print("\n== RUNNING CANDIDATE ===============\n", verbose)
        candidate_path = os.path.join(self.base_dir, self.candidate_dir)
        clean_exit = True
        
        # Termination Conditions (Code will exit if following tests fail)
        
        self.__print("1. Loading Settings.json\n", verbose)
        settings = self.loadSettings(verbose);
        if(settings == False):
            return False
        
        self.__print("2. Copying Input Files to Program\n", verbose)
        if(not self.copyInputFilesToProgramDir(candidate_path, settings, verbose)):
            return False

        self.__print("3. Compilation\n", verbose)
        if(not self.makeAll(candidate_path, verbose)):
            return False
        
        # Test Conditions (Code will not return if tests fail)
        
        self.__print("4. Running Programs\n", verbose)
        clean_exit = self.execPrograms(settings, candidate_path, verbose) and clean_exit

        self.__print("5. Verifying Output Files Exist\n", verbose)
        clean_exit = self.allOutputFilesFound(settings, candidate_path, verbose) and clean_exit
            
        self.__print("6. Comparing Output To Key\n", verbose)
        result = self.compareOutputFilesWithKey(settings, candidate_path, verbose)
        clean_exit = clean_exit and result['flag']
        
        self.__print("\n== END TEST ========================\n", verbose)
        return {'flag' : clean_exit, 'score' : result['score'], 'total' : result['total']}


    def runKey(self, verbose):
     # Execute programs in key folder and store outputs in key_output_files
        self.__print("\n== GENERATING KEY ===============\n", verbose)
        key_path = os.path.join(self.base_dir, "key")
        
        self.__print("1. Loading Settings.json\n", verbose)
        settings = self.loadSettings(verbose);
        if(settings == False):
            return False
        
        self.__print("2. Compilation\n", verbose)
        if(not self.makeAll(key_path, verbose)):
            return False
            
        self.__print("3. Generating Input Files\n", verbose)
        if(not self.generateInputFiles(key_path, settings, verbose)):
            return False
        
        self.__print("4. Running Programs\n", verbose)
        if(not self.execPrograms(settings, key_path, verbose)):
            return False

        self.__print("5. Verifying Output Files Exist\n", verbose)
        if(not self.allOutputFilesFound(settings, key_path, verbose)):
            return False
            
        self.__print("6. Copying Output Files To key_output_files\n", verbose)
        if(not self.copyOutputFilesToKey(settings, key_path, verbose)):
            return False
            
        self.__print("7. Running \"make clean\"", verbose)
        self.__shellcmd("make clean", key_path)
        
        self.__print("\n=================================\n", verbose)
        
        return True
        
    def emptyCandidateFolder(self, verbose):
    # empties candidate folder by deleting and recreating it
    
        candidate_path = os.path.join(self.base_dir, self.candidate_dir)
        try:
            shutil.rmtree(candidate_path, ignore_errors=False)
            os.makedirs(candidate_path)
            return True
        except:
            return False
    
    def loadSettings(self, verbose):
    # Loads settings.json. NOTE: Code does not currently verify structure is valid
    
        settings_path = os.path.join(self.base_dir, self.settings_file)
        if(not os.path.exists(settings_path)):
            self.__print("\tFAIL (settings.json does not exist)\n", verbose)
            return False
        try:
            self.__print("\tPASS\n", verbose)
            return json.load(open(settings_path, 'r'))
        except ValueError, e:
            self.__print("\tFAIL (settings.json contains invalid JSON string)\n", verbose)
            return False

    def makeAll(self, program_dir, verbose):
    # runs make all inside specified directory.
    # PARAMETERS:
    #   program_dir (string) - location of makefile and c++ code
    # RETURNS:
    #   bool - true if make returned with no error, false otherwise
    
        self.__print('\t$ make all', verbose)
        exit_code = self.__shellcmd('make all', program_dir)

        if(exit_code == 'TO'):
            self.__print('\t\tFAIL: command timed out\n', verbose)
        elif(exit_code != 0):
            self.__print('\t\tFAIL: exited with error\n', verbose)
            return False
        else:
            self.__print('\t\tPASS\n', verbose)
            return True

    def generateInputFiles(self, program_dir, settings, verbose):
        
        # run commands to generate files
        for command in settings['input_files']['commands']:
            self.__shellcmd(command, program_dir)
        
        # check that all input files exist and copy to input_files_dir
        clean_exit = True
        for file_name in settings['input_files']['names']:
            file_path = os.path.join(program_dir, file_name)
            if(not os.path.exists(file_path)):
                self.__print("\t" + file_name + "\n\t> Missing", verbose)
                clean_exit = False
            else:
                dst_path = os.path.join(self.base_dir, self.input_file_dir, file_name)
                try:
                    shutil.copyfile(file_path, dst_path)
                    self.__print("\t" + file_name + "\n\t\tExists & Copied\n", verbose)
                except:
                    self.__print("\t" + file_name + "\n\t\tExists but could not be Copied\n", verbose)
                    clean_exit = False
        return clean_exit

    def copyInputFilesToProgramDir(self, program_dir, settings, verbose):
    # copies all output files to the key_output_files folder
    #   settings (dictionary) - grading settings
    #   program_dir (string) - location of makefile and c++ code
    
        for file_name in settings['input_files']['names']:
            src_path = os.path.join(self.base_dir, self.input_file_dir, file_name)
            dst_path = os.path.join(program_dir, file_name)

            try:
                shutil.copyfile(src_path, dst_path)
                self.__print("\tcopyied " + file_name + "\n", verbose)
            except:
                self.__print("\tERROR: could not copy " + file_name + "\n", verbose)
                return False

        return True

    def execPrograms(self, settings, program_dir, verbose):
    # runs all commands specified settings files inside specified directory.
    # PARAMETERS:
    #   settings (dictionary) - grading settings
    #   program_dir (string) - location of makefile and c++ code
    # RETURNS:
    #   array - contains exit codes for each command

        clean_exit = True
        for program in settings['programs']:
            exit_code = self.__shellcmd(program['command'], program_dir)
            if(exit_code == 'TO'):
                self.__print('\t  FAIL (command timed out)', verbose)
            elif(exit_code != program['exit_code']):
                self.__print("\t$ " + program['command'] + "\n\t\tFAIL (returned exit code " + str(exit_code) + ", expected " + str(program['exit_code']) + ")\n", verbose)
                clean_exit = False
            else:
                self.__print("\t$ " + program['command'] + "\n\t\tEXIT CODE CORRECT\n", verbose)
    
        return clean_exit

    def allOutputFilesFound(self, settings, program_dir, verbose):
    #   settings (dictionary) - grading settings
    #   program_dir (string) - location of makefile and c++ code
    
        clean_exit = True
        output_file_names = self.__allOutputFileNames(settings)
        
        for file_name in output_file_names:
            file_path = os.path.join(program_dir, file_name)
            if(not os.path.exists(file_path)):
                self.__print("\t" + file_name + "\n\t\tMissing!\n", verbose)
                clean_exit = False
            else:
                self.__print("\t" + file_name + "\n\t\tExists\n", verbose)
        
        return clean_exit
    
    def copyOutputFilesToKey(self, settings, program_dir, verbose):
    # copies all output files to the key_output_files folder
    #   settings (dictionary) - grading settings
    #   program_dir (string) - location of makefile and c++ code
    
        output_file_names = self.__allOutputFileNames(settings)
        key_output_path = os.path.join(self.base_dir, "key_output_files")
        
        for file_name in output_file_names:
            src_path = os.path.join(program_dir, file_name)
            dst_path = os.path.join(self.base_dir, "key_output_files", file_name)
            try:
                shutil.copyfile(src_path, dst_path)
                self.__print("\tcopyied " + file_name, verbose)
            except:
                self.__print("\tERROR: could not copy " + file_name, verbose)
                return False
        
        return True
        
    def compareOutputFilesWithKey(self, settings, program_dir, verbose):
    # copies all output files to the key_output_files folder
    #   settings (dictionary) - grading settings
    #   program_dir (string) - location of makefile and c++ code
    
        score = 0
        total = 0
        
        flag = True
        num_files = len(settings['output_files']);
        for i in range(0, num_files):
            file = settings['output_files'][i]
            file_name = file['name']
            points = file['points']
            rules = {'operator' : file['operator'], 'tolerance' : file['tolerance']}
            
            
            file_path = os.path.join(program_dir, file_name);
            key_path = os.path.join(self.base_dir, "key_output_files", file_name)
            result = self.equivalentTextFiles(key_path, file_path, rules)

            if(not result['equal']):
                self.__print("\t" + file_name + "\n\t\tFAIL - " + result['error_message'] + "\n", verbose)
                flag = False;
            else:
                self.__print("\t" + file_name + "\n\t\tPASS (+" + str(points) + "pts)\n", verbose)
                score = score + points;
            total = total + points;
    
        return {'flag' : flag, 'score' : score, 'total' : total}

    def __allOutputFileNames(self, settings):
    # returns list of all output files from settings dictionary
    
        file_names    = lambda file : str(file['name']) # returns string file names for a file
        names = map(file_names, settings['output_files']) # extract all output filenames from settings dictionary
        return names



    # == START FILE COMPARISON FUNCTIONS ======================================================================

    def equivalentTextFiles(self, file_a_path, file_b_path, rules):
    # Compares two text files to determine if they are equivalent. Equivalence for each line of the text files
    # is determined using the equivalentStrings function.
    # PARAMETERS:
    #   file_path_a (string) string containing full path to file_a
    #   file_path_b (string) string containing full path to file_b
    #   numerical_tolerance (double >= 0) maximum absolute difference allowed for numerical values
    # RETURNS:
    #   associative array - {'Equal' }
    
        if(not os.path.exists(file_a_path)):
            return {"equal" : False, "error_code" : 1, "error_message" : "file " + file_a_path + " does not exist"}
        
        if(not os.path.exists(file_b_path)):
            return {"equal" : False, "error_code" : 1, "error_message" : "file " + file_b_path + " does not exist"}
    
        file_a_obj = open(file_a_path, 'r');
        file_b_obj = open(file_b_path, 'r');
        
        file_a_lines = file_a_obj.read().splitlines();
        file_b_lines = file_b_obj.read().splitlines();
    
        if(len(file_a_lines) != len(file_b_lines)):
            return {"equal" : False, "error_code" : 1, "error_message" : "unequal file length"}
    
        for i in range(0, len(file_a_lines)):
            result = self.equivalentStrings(file_a_lines[i], file_b_lines[i], rules)
            if(not result['equal']):
                return {"equal" : False, "error_code" : 2, "error_message" : "line " + str(i+1) + " does not match (" + result['message'] + ")"}
        
        file_a_obj.close()
        file_b_obj.close()
        return {"equal" : True, "error_code" : 0, "error_message" : ""}
        
        
    def equivalentStrings(self, line_a, line_b, rules):
    # Compares two strings to determine if they are equivalent.
    # PARAMETERS:
    #   line_a (string) string from file a
    #   line_b (string) string from file b
    #   numerical_tolerance (double >= 0) maximum absolute difference allowed for numerical values
    # RETURNS:
    #   bool - true if lines are equivalent, false otherwise
    #
    #  NOTE: equivalence is determined differently depending on structure of strings.
    #  Each Case is described below.
    #
    #   1. both lines contain at least one numeric values separated by whitespace
    #      RETURNS True if the absolute difference between each numerical values is within numerical_tolerance parameter
    #
    #   2. otherwise
    #      RETURNS True if strings are equal ignoring capitals. WARNING: does not support special characters.

        line_is_numerical = lambda line : bool(line.strip()) and all(map(lambda x : self.isFloat(x), line.split()))
        get_floats        = lambda line : map(float, line.split())
        
        line_a_is_numerical = line_is_numerical(line_a)
        if(line_a_is_numerical):
            floats_a = get_floats(line_a)
        line_b_is_numerical = line_is_numerical(line_b)
        if(line_b_is_numerical):
            floats_b = get_floats(line_b)
        
        # -- Generic Failure Conditions ------------------------------------
        if(line_a_is_numerical and line_b_is_numerical):
            if(len(floats_a) != len(floats_b)):
                return {"equal" : False, "message" : "expected " + str(len(floats_a)) + " numerical values but found " + str(len(floats_b))}
        elif(line_a_is_numerical and (not line_b_is_numerical)):
            return {"equal" : False, "message" : "expected numerical value but found string instead"}
        if((rules['operator'] == 'gt' or rules['operator'] == 'lt') and (not line_a_is_numerical or not line_b_is_numerical)):
            return {"equal" : False, "message" : "expected numerical value but found string instead"}
        
        # -- Special Flag based Comparisons -------------------------------
        if(rules['operator'] == 'skip'): # skip comparison and return true
            return {"equal" : True, "message" : ""}
        elif(rules['operator'] == 'gt'): # greater than comparison
            if(all(map(operator.gt, floats_a, floats_b))):
                return {"equal" : True, "message" : ""}
            else:
                return {"equal" : False, "message" : "greater then condition was not satisfied"}
        elif(rules['operator'] == 'lt'): # less than comparison
            if(all(map(operator.lt, floats_a, floats_b))):
                return {"equal" : True, "message" : ""}
            else:
                return {"equal" : False, "message" : "less then condition was not satisfied"}
        elif(rules['operator'] == 'eq'): # equality comparison
            if(line_a_is_numerical and line_b_is_numerical):
                if(max(map(lambda x,y : abs(x-y), floats_a, floats_b)) <= rules['tolerance']): # max(abs(x - y)) <= tol
                    return {"equal" : True, "message" : ""}
                else:
                    return {"equal" : False, "message" : "numeric values are not within required tolerance"}
            elif(line_a == line_b):
                return {"equal" : True, "message" : ""}
            else:
                return {"equal" : False, "message" : "unequal strings"}
        else:
            return {"equal" : False, "message" : "invalid operator"}
            
    def isFloat(self, x):
        try:
            float(x)
            return True
        except ValueError:
            return False


    # == END FILE COMPARISON FUNCTIONS ======================================================================

    # == START SHELL & OUTPUT FUNCTIONS =============================================================================

    def __shellcmd(self, str_command, wd="", max_timeout=10):
    # runs shell command and returns exit code

        FNULL = open(os.devnull, 'w') # redirect standard out and standard err to FNULL to avoid printing
        kill = lambda process: process.kill()
        
        proc = subprocess.Popen(str_command, shell=True, cwd=wd, stdout=FNULL, stderr=FNULL)
        my_timer = Timer(max_timeout, kill, [proc])
        
        # ALLOW FOR TIMEOUT : https://www.blog.pythonlibrary.org/2016/05/17/python-101-how-to-timeout-a-subprocess/
        try:
            my_timer.start()
            proc.communicate()
            return proc.returncode
        finally:
            my_timer.cancel()

    def __print(self, message, verbose):
        if(verbose):
            print message

    # == END SHELL & OUTPUT FUNCTIONS ===============================================================================


grader_type = "student" # "cmd" or "student"

## === STUDENT VERSION ========================================================
if(grader_type == "student"):
    file_dir = os.path.dirname(__file__); # directory where this file is located
    grader = CppGrader(file_dir);
    results = grader.runCandidate(True)
    if(results == False):
        print("\n\tcode was not graded due to errors ===\n")
    else:
        print("\n\tscore: " + str(results['score']) + "/" + str(results['total']) + "\n")

