function [] = plot_dat(filename)
%plot_dat Plot the data from the specified .dat file filled with integers
%   The .dat file should be in the same file as the function.
%   You will have to zoom into the plot to appreciate it.
%   Change the %d to suitable format specifier to view .dat files with
%   floating point or any other format values.

fid = fopen(filename, 'r');
input_data=fscanf(fid,'%d');
figure, plot(input_data);
fclose(fid);
end