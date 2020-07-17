#!/bin/env python3
"""
Tora database
"""

# defaults
import csv

# siki
from siki.basics import FileUtils
from siki.basics import Hashcode

TORA_CSV=".tora/file.csv"

def create_tora_db(path=TORA_CSV):
    if not FileUtils.exists(".tora"):
        FileUtils.mkdir(".tora")

    if not FileUtils.exists(path):
        FileUtils.touch_file(path)

    return read_tora_db(path)


def read_tora_db(path=TORA_CSV):
    """
    load tora db
    """
    # load data from db
    database = {}
    with open(path, 'r') as f:
        reader = csv.reader(f)
        for row in reader:
            database[row[0]] = row[1]

    # return to caller
    return database


def write_tora_db(database, path=TORA_CSV):
    """
    write update back to file
    """
    # write back
    with open(path, 'w') as f:
        writer = csv.writer(f)
        for key, val in database.items():
            writer.writerow([key, val])


def temp_file_not_exists(srcfile):
    from CompileSrc import object_name
    obj_file = object_name(srcfile)
    return not FileUtils.exists(obj_file)


def update_tora_hash(filename, database):
    """
    load data from file, and generate file hash code
    """
    if not FileUtils.exists(filename) or type(database) is not dict:
        return False

    # calculate file md5
    md5 = Hashcode.compute_file_md5(filename)

    # check original filename md5
    omd5 = ""
    if filename in database.keys():
        omd5 = database[filename]

    # not record this file
    if omd5 is None:
        database[filename] = md5
        return True
    if md5 != omd5:
        database[filename] = md5
        return True
    if temp_file_not_exists(filename):
        database[filename] = md5
        return True
    
    return False


if __name__ == "__main__":
    create_tora_db()
    db = read_tora_db()

    flist = FileUtils.search_files(".", ".py$")
    for f in flist:
        update_tora_hash(f, db)
    
    write_tora_db(db)

