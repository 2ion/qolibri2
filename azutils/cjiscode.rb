#!/usr/bin/env ruby

reserve_code = 0xe000
File.readlines(ENV['HOME'] + "/.azutils/JIS-CODE.txt").each{|line|
  l = line.split(/	/)
  u = l[3].sub("U+","")
  if u.nil?
    puts l[0] + ":0"
  else
    if u.index("+").nil?
      puts l[0] + ":" + u
    else
      puts l[0] + ":" + ("%X" % reserve_code) + "," + u
      reserve_code = reserve_code + 1
    end
  end
}
