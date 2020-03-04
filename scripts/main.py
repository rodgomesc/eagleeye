# encoding=utf-8
# @Time    : 17-7-25
# @File    : main.py
# @Author  : jian<jian@mltalker.com>

from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals
from jinja2 import Environment, FileSystemLoader
import sys
import os
from flags import *
import flags

flags.DEFINE_string('project', None, 'project name')
flags.DEFINE_string("version", None, "project version")
flags.DEFINE_string("signature",None, "projct signature")
flags.DEFINE_string("opencv", "", "opencv path")
flags.DEFINE_string("snpe","","snpe path")
flags.DEFINE_string("mace","","mace path")
flags.DEFINE_string("eagleeye", "", "eagleeye path")
flags.DEFINE_string("abi", "arm64-v8a", "abi")
flags.DEFINE_string("build_type","Release","set build type")
flags.DEFINE_string("api_level","android-23", "android api level")
flags.DEFINE_boolean("neon", True, "support neon")
flags.DEFINE_boolean("opencl", True, "support opencl")
flags.DEFINE_string("node", "NODE", "node name")
flags.DEFINE_string("inputport", "", "input port list")
flags.DEFINE_string("outputport","", "output port list")

FLAGS = flags.AntFLAGS
def main():
    # 模板引擎
    template_file_folder = os.path.join(os.path.dirname(__file__), 'templates')
    file_loader = FileSystemLoader(template_file_folder)
    env = Environment(loader=file_loader)

    if(sys.argv[1] == 'node'):
      flags.cli_param_flags(sys.argv[2:])
      
      # 生成节点模板
      project_name = FLAGS.project()
      node_name = FLAGS.node()
      # 生成node.h
      template = env.get_template('project_node_h.template')
      inputport_list_str = FLAGS.inputport()
      inputport_list = inputport_list_str.split(',')

      outputport_list_str = FLAGS.outputport()
      outputport_list = outputport_list_str.split(',')

      output = template.render(MYNODE=node_name.upper(),
                                inputport=inputport_list,
                                outputport=outputport_list)
      if not os.path.exists(os.path.join(os.curdir, "%s_plugin"%project_name)):
          os.mkdir(os.path.join(os.curdir, "%s_plugin"%project_name))
          return
      
      with open(os.path.join(os.curdir, "%s_plugin"%project_name, "%s.h"%node_name),'w') as fp:
        fp.write(output)

      # 生成node.cpp
      template = env.get_template('project_node_cpp.template')
      output = template.render(MYNODE=node_name.upper(),
                                inputport=inputport_list,
                                outputport=outputport_list)
      if not os.path.exists(os.path.join(os.curdir, "%s_plugin"%project_name)):
          os.mkdir(os.path.join(os.curdir, "%s_plugin"%project_name))
          return
      
      with open(os.path.join(os.curdir, "%s_plugin"%project_name, "%s.cpp"%node_name),'w') as fp:
        fp.write(output)

      return

    # 生成插件模板
    flags.cli_param_flags(sys.argv[1:])
    project_name = FLAGS.project()
    project_version = FLAGS.version()
    project_signature = FLAGS.signature()

    # 生成插件头文件
    template = env.get_template('project_plugin_header.template')
    output = template.render(project=project_name)

    if not os.path.exists(os.path.join(os.curdir, "%s_plugin"%project_name)):
        os.mkdir(os.path.join(os.curdir, "%s_plugin"%project_name))
    
    with open(os.path.join(os.curdir, "%s_plugin"%project_name, '%s_plugin.h'%project_name),'w') as fp:
      fp.write(output)

    # 生成插件源文件
    template = env.get_template('project_plugin_source.template')
    output = template.render(project=project_name,
                             version=project_version,
                             signature=project_signature)

    if not os.path.exists(os.path.join(os.curdir, "%s_plugin"%project_name)):
        os.mkdir(os.path.join(os.curdir, "%s_plugin"%project_name))
    
    with open(os.path.join(os.curdir, "%s_plugin"%project_name, '%s_plugin.cpp'%project_name),'w') as fp:
      fp.write(output)

    # 生成CMakeList.txt
    template = env.get_template('project_plugin_cmake.template')
    output = template.render(project=project_name,
                             eagleeye=FLAGS.eagleeye(),
                             abi=FLAGS.abi(),
                             opencv=FLAGS.opencv(),
                             opencl=FLAGS.opencl(),
                             neon=FLAGS.neon())

    if not os.path.exists(os.path.join(os.curdir, "%s_plugin"%project_name)):
        os.mkdir(os.path.join(os.curdir, "%s_plugin"%project_name))
    
    with open(os.path.join(os.curdir, "%s_plugin"%project_name, "CMakeLists.txt"),'w') as fp:
      fp.write(output)

    # 生成build.sh
    template = env.get_template('project_shell.template')
    output = template.render(abi=FLAGS.abi(),
                             build_type=FLAGS.build_type(),
                             api_level=FLAGS.api_level())

    if not os.path.exists(os.path.join(os.curdir, "%s_plugin"%project_name)):
        os.mkdir(os.path.join(os.curdir, "%s_plugin"%project_name))
    
    with open(os.path.join(os.curdir, "%s_plugin"%project_name, "build.sh"),'w') as fp:
      fp.write(output)

    # 生成demo.cpp
    template = env.get_template('project_demo.template')
    output = template.render(project=project_name)

    if not os.path.exists(os.path.join(os.curdir, "%s_plugin"%project_name)):
        os.mkdir(os.path.join(os.curdir, "%s_plugin"%project_name))
    
    with open(os.path.join(os.curdir, "%s_plugin"%project_name, '%s_demo.cpp'%project_name),'w') as fp:
      fp.write(output)

    # 生成说明文档
    

if __name__ == '__main__':
  main()