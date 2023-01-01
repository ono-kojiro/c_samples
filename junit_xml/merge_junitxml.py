#!/usr/bin/python3
import os
import re
import sys

import getopt

from pathlib import Path

import subprocess
import shlex
import shutil

from lxml import etree

from pprint import pprint

def usage():
    print("Usage : {0}".format(argv[0]))

def find_xmlfiles(dirlist) :
    items = []

    for dirpath in dirlist :
        for path in Path(dirpath).rglob('*.xml') :
            items.append(str(path))

    return items

def validate_junit_xml(xmlfiles) :
    items = []

    for filepath in xmlfiles :
        cmd = "xmllint --noout --schema ./junit-10.xsd "
        cmd += "{0}".format(filepath)
        #print(cmd)
        # ok
        #ret = subprocess.check_call(shlex.split(cmd))
            
        try :
            ret = subprocess.check_output(
                shlex.split(cmd),
                stderr=subprocess.STDOUT,
            )
        except subprocess.CalledProcessError as e:
            #pprint(e)
            continue

        items.append(filepath)
    return items

def main():
    ret = 0

    try:
        opts, args = getopt.getopt(
            sys.argv[1:],
            "hvo:e:",
            [
                "help",
                "version",
                "output=",
                "expr=",
            ],
        )
    except getopt.GetoptError as err:
        print(str(err))
        sys.exit(2)

    output = None

    for o, a in opts:
        if o == "-v":
            usage()
            sys.exit(0)
        elif o in ("-h", "--help"):
            usage()
            sys.exit(0)
        elif o in ("-o", "--output"):
            output = a

    if ret != 0:
        sys.exit(1)

    if output is not None:
        fp = open(output, mode="w", encoding="utf8")
    else:
        fp = sys.stdout

    if len(args) == 0 :
        dirlist = [ "." ]
    else :
        dirlist = args

    xmlfiles = find_xmlfiles(dirlist)

    junit_xmls = validate_junit_xml(xmlfiles)

    new_root = None

    testsuites = []

    for filepath in junit_xmls :
        print('parse {0}'.format(filepath))
        tree = etree.parse(filepath)
        root = tree.getroot()
        #print(root.tag)

        if new_root is None :
            new_root = root
            continue

        for testsuite in root.findall('testsuite') :
            new_root.append(testsuite)

    etree.indent(new_root, space="    ")
    fp.write(etree.tostring(new_root, pretty_print=True).decode())

    if output is not None:
        fp.close()

if __name__ == "__main__":
    main()
