#!/usr/bin/ruby

require 'socket'
starttime = Process.clock_gettime(Process::CLOCK_MONOTONIC)
s = TCPSocket.new 'localhost' , 8989
$i = 0
$j = 0

BEGIN {   
    puts"Hello Player!!"
    puts"Lets play tic tac toe"
    puts"In order to make your move, type the column number follwed by row number referring as"
    puts"|00|01|02|"
    puts"|10|11|12|"
    puts"|20|21|22|"  
 }


for i in 0..9 

    # puts "current board state"
    # prev0 = s.gets
    # puts prev0
    # prev1 = s.gets.
    # puts prev1
    # prev2 = s.gets
    # puts prev2
    
    # # ifturn = s.gets
    # puts ifturn
    

    puts"Your move: "

    move = STDIN.gets.chomp
    s.write("#{move}")
    # s.each_line do |line|
    #     puts line
    # end
    puts "current state"
    linex = s.gets   
    puts linex
    line2x = s.gets
    puts line2x
    line3x = s.gets
    puts line3x
    
    line = s.gets   
    puts line
    line2 = s.gets
    puts line2
    line3 = s.gets
    puts line3

    line4 = s.gets
    puts line4

  


    
end

s.close


endtime = Process.clock_gettime(Process::CLOCK_MONOTONIC)
elapsed = endtime - starttime
puts "ELAPSED:  #{elapsed} (#{ARGV[0]})" 

#!/usr/bin/env ruby -w
# require "socket"
# class Client
#   def initialize( server )
#     @server = server
#     @request = nil
#     @response = nil
#     listen
#     send
#     @request.join
#     @response.join
#   end

#   def listen
#     @response = Thread.new do
    #   loop {
    #     msg = @server.gets.chomp
    #     puts "#{msg}"
    #   }
#     end
#   end

#   def send
#     puts "Enter your move:"
#     @request = Thread.new do
#       loop {
#         msg = $stdin.gets.chomp
#         @server.puts( msg )
#       }
#     end
#   end
# end

# server = TCPSocket.open( "localhost", 8989)
# Client.new( server )