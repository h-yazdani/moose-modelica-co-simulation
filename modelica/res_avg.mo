impure function res_avg 
  input String input_file_path;  // Path to the input CSV file
  input String output_file_path; // Path to the output CSV file

external "C" resfunction(input_file_path,output_file_path)
  annotation (
  Include="#include <resfunction.c>",  // Include the C source file
  IncludeDirectory="modelica://Buildings/Resources/C-Sources");
end res_avg; 
