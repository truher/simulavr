# -*- coding: UTF-8 -*-
# Python script to create page pattern and expected checksums for regression
# test SPM operation on simulavr. Writes C defines to stdout for pages with 16,
# 32, 64 and 128 words and defines for expected checksums to include in test
# program. For every page size 2 pattern with checksum will be written.

def calculate_checksum(pattern):
  i_sum = 0
  i_xor = 0
  for i in pattern:
    i_sum += i
    i_xor ^= i
  return (i_sum & 0xff) + ((i_xor & 0xff) << 8)
  
def create_pattern(size, pattern2):
  size *= 2 # given as word size, calculate byte size
  if pattern2:
    p_string = "this is self programmed "
  else:
    p_string = "this is flashed by programmer "
  result = list()
  idx = 0
  for i in range(size):
    v = ord(p_string[idx])
    idx += 1
    if idx >= len(p_string): idx = 0
    result.append(v)
  return result

def write_pattern(pattern, name):
  print "#define %s { \\" % name
  while len(pattern) > 0:
    p = pattern[:8]
    pattern = pattern[8:]
    s = ", ".join(["0x%02x" % s for s in p])
    if len(pattern) > 0: s += ","
    print "    %s \\" % s
  print "  }"

def write_checksum(chksum, name):
  print "#define %s 0x%04x" % (name, chksum)

def write_head():
  print "/* Pattern for regression test SPM operation for simulavr. */"
  print "/* Automatically created, do not change! */"
  print "#ifndef __PAGE_PATTERN_H__"
  print "#define __PAGE_PATTERN_H__"
  
def write_tail():
  print "#endif /* ifndef __PAGE_PATTERN_H__ */"

if __name__ == "__main__":
  
  write_head()
  for size in (16, 32, 64, 128):
    p1 = create_pattern(size, False)
    s1 = calculate_checksum(p1)
    write_pattern(p1, "PAGE_PATTERN_1_%d" % (size * 2))
    write_checksum(s1, "CHKSUM_PATTERN_1_%d" % (size * 2))
    p2 = create_pattern(size, True)
    s2 = calculate_checksum(p2)
    write_pattern(p2, "PAGE_PATTERN_2_%d" % (size * 2))
    write_checksum(s2, "CHKSUM_PATTERN_2_%d" % (size * 2))
  write_tail()
  
# EOF
