function [sqwv] = square_wave()
%square_wave Plots a square wave of amplitude 2^(15)-1
%   outputs an array named sqwv which contains 128 "2^(15)-1"s and 128
%   "-2^(15)"s. To form a dat file, just copy and paste the contents of the
%   sqwv into it. Don't forget to give the header correct.
%   You can customize this function, as you want.

sqwv = int16(zeros(256,1));
sqwv(1:128,1)=32767;
sqwv(129:256,1)=-32768;
end