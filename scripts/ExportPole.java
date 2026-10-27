import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.io.*;
import ghidra.program.model.symbol.SourceType;

public class ExportPole extends GhidraScript {
 public void run() throws Exception {
  File out = new File(getScriptArgs()[0]); out.mkdirs();
  String[][] names={
   {"1000:0053","pole_load_resources"},{"1000:03a5","pole_draw_font"},
   {"1000:05ca","pole_init_ega_palette"},{"1000:08e4","pole_speaker_transition"},
   {"1000:09a4","pole_draw_score"},{"1000:1034","pole_host_dialogue"},
   {"1000:1698","pole_reveal_and_award"},{"1000:1a3a","pole_select_letter"},
   {"1000:1fcf","pole_plus_select_position"},{"1000:24bd","pole_normalize_key"},
   {"1000:254e","pole_guess_full_word"},{"1000:27db","pole_enter_highscore_name"},
   {"1000:29f1","pole_load_word_pair"},{"1000:2b4e","pole_draw_wheel"},
   {"1000:2c6a","pole_spin_wheel"},{"1000:31cb","pole_bonus_chests"},
   {"1000:37eb","pole_choice_prompt"},{"1000:3b8a","pole_intro"},
   {"1000:42b4","pole_prize_negotiation"},{"1000:47bd","pole_final_highscores"},
   {"1000:4f66","pole_credits"},{"1000:53b3","pole_introduce_players"},
   {"1000:5e81","pole_blit_rle"},{"1a77:02c6","pc_speaker_sound_hz"},
   {"1a77:02f3","pc_speaker_no_sound"},{"1a77:029e","pascal_delay_ms"},
   {"1ad9:1150","pascal_random_bound"},{"1ad9:119f","pascal_random_next"}
  };
  try(PrintWriter manifest=new PrintWriter(new File(out,"functions.tsv"))){
   manifest.println("address\tname");
   for(String[] entry:names){Function f=getFunctionAt(toAddr(entry[0]));if(f!=null){f.setName(entry[1],SourceType.USER_DEFINED);manifest.println(entry[0]+"\t"+entry[1]);}}
  }
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
