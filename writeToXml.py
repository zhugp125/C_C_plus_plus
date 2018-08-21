#!/usr/bin/env python3
# _*_ coding: utf-8 _*_

from collections import namedtuple
from xml.dom.minidom import Document

def readFile(filename, lines):
    with open(filename, 'r') as f:
        for line in f:
            line = line.rstrip(' \n')
            if line.startswith('//') or len(line) == 0:
                continue
            lines.append(line)

def writeXml(filename, lines, tagNames):
    # 创建doc
    doc = Document()
    # 创建根节点
    root = doc.createElement(tagNames[0])
    doc.appendChild(root)

    # 记录每层节点的最新元素
    nodes = {0: root}

    for line in lines:
        index = line.rfind(' ')
        level = (index + 1) / 4 + 1
        line = line.lstrip(' ')
        
        node = doc.createElement(tagNames[level])
        node.setAttribute('name', line)

        nodes[level - 1].appendChild(node)
        nodes[level] = node

    with open(filename, 'w') as f:
        f.write(doc.toprettyxml(indent='\t'))

def display(lines):
    for line in lines:
        print(line)

if __name__ == '__main__':
    lines = []
    readFile('./file/sector.txt', lines)

    tagNames = ['SectorFile', 'Sectors', 'sector', 'sector_second']
    writeXml('./file/sector.xml', lines, tagNames)