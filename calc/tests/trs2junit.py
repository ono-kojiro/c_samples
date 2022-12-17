#!/usr/bin/env python3

import sys
import os
import re

import getopt

from junit_xml import TestSuite, TestCase

from pprint import pprint

def usage():
    print(f"Usage : {sys.argv[0]} -o <output> <input>...")


def main():
    ret = 0

    try:
        options, args = getopt.getopt(
            sys.argv[1:],
            "hvo:",
            [
                "help",
                "version",
                "output=",
            ],
        )
    except getopt.GetoptError as err:
        print(str(err))
        sys.exit(1)

    output = None

    for option, optarg in options:
        if option == "-v":
            usage()
            sys.exit(1)
        elif option in ("-h", "--help"):
            usage()
            sys.exit(1)
        elif option in ("-o", "--output"):
            output = optarg
        else:
            assert False, "unknown option"

    # if output == None :
    # 	print('no output option')
    # 	ret += 1

    if ret != 0:
        sys.exit(ret)

    if output is None:
        fp = sys.stdout
    else:
        fp = open(output, mode="w", encoding="utf-8")

    test_cases = []

    for filepath in args:
        testname = os.path.splitext(os.path.basename(filepath))[0]
        
        record = {
            "test-name" : testname
        }

        fp_in = open(filepath, mode="r", encoding="utf-8")
        while 1 :
            line = fp_in.readline()
            if not line :
                break
            
            line = re.sub(r'\r?\n?$', '', line)

            m = re.search(r'^:([\w\-_]+): (.+)', line)
            if m :
                param = m.group(1)
                value = m.group(2)
                record[param] = value
            else :
                print('invalid line, {0}'.format(line))
                sys.exit(1)

        test_case = TestCase(
            record['test-name'],
            elapsed_sec=float(record['real-time'])
        )
        
        if record['global-test-result'] == 'FAIL' :
            msg = '{0} failed'.format(record['test-name'])
            test_case.add_failure_info(msg)

        test_cases.append(test_case)

    ts = TestSuite("testsuite", test_cases)

    fp.write(TestSuite.to_xml_string([ts]))
        
    if output is not None:
        fp.close()


if __name__ == "__main__":
    main()
