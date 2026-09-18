impure function ModelicaSwitchFunction

external "C" ModelicaSwitchFunction()
  annotation (
  Include="#include <ModelicaSwitch.c>",
  IncludeDirectory="modelica://Buildings/Resources/C-Sources");

end ModelicaSwitchFunction;
