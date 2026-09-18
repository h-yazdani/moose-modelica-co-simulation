impure function csvWriter

  input String filename "Name of data file";
  input Real col1;
  input Real col2;
  input Real col3;
  input Real col4;
  input Real col5;
  
external "C" csvwriter(filename, col1, col2, col3, col4, col5)
  annotation (
  Include="#include <csvWriter.c>",
  IncludeDirectory="modelica://Buildings/Resources/C-Sources");
end csvWriter;
  
