import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.io.*;
import ghidra.program.model.symbol.SourceType;

public class ExportHotseat extends GhidraScript {
 public void run() throws Exception {
  File out = new File(getScriptArgs()[0]); out.mkdirs();
  DecompInterface d = new DecompInterface(); d.openProgram(currentProgram);
  try(PrintWriter c = new PrintWriter(new File(out,"decompiled.c"));
      PrintWriter a = new PrintWriter(new File(out,"listing.asm"))) {
   FunctionIterator fs = currentProgram.getFunctionManager().getFunctions(true);
   while(fs.hasNext() && !monitor.isCancelled()) {
    Function f=fs.next(); c.println("\n/* "+f.getEntryPoint()+" "+f.getName()+" */");
    DecompileResults r=d.decompileFunction(f,30,monitor);
    if(r.decompileCompleted()) c.println(r.getDecompiledFunction().getC());
    else c.println("/* FAILED: "+r.getErrorMessage()+" */");
   }
   InstructionIterator is=currentProgram.getListing().getInstructions(true);
   while(is.hasNext()) {Instruction i=is.next();a.println(i.getAddress()+"  "+i);}
  } finally {d.dispose();}
  println("POLE_EXPORT_COMPLETE functions="+currentProgram.getFunctionManager().getFunctionCount());
 }
}
