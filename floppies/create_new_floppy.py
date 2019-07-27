#!/usr/bin/env python3
# A simple script for creating a new floppy project.

import argparse
from distutils.dir_util import copy_tree

TEMPLATE_DIR = './template'


# Parse all arguments
arg_parser = argparse.ArgumentParser(description='Creates a new floppy project.')
arg_parser.add_argument('project_name', help='The name of the project.')
arg_parser.add_argument('--description', default='A floppy project.', help='A sentence describing the project.')

args = arg_parser.parse_args()

# Create the project from the template
project_dir = './' + args.project_name
try:
    copy_tree(TEMPLATE_DIR, project_dir)
    print('Created project in', project_dir)
except DistutilsFileError:
    print('Could not create the project!')
    exit()

# Build the keyword map
keyword_map = {
    'PROJECT_NAME': args.project_name,
    'DESCRIPTION': args.description
}


# Update all listed files with keyword map entries
def update_project_file(file_name):
    file_path = project_dir + '/' + file_name
    file_string = open(file_path).read()
    for keyword in keyword_map:
        keyword_pattern = '{{' + keyword.upper() + '}}'
        file_string = file_string.replace(keyword_pattern, keyword_map[keyword])
    file_handle = open(file_path, 'w')
    file_handle.write(file_string)
    file_handle.close()


update_project_file('README.md')
update_project_file('CMakeLists.txt')
update_project_file('source/CMakeLists.txt')
update_project_file('source/library/CMakeLists.txt')
update_project_file('tests/CMakeLists.txt')
