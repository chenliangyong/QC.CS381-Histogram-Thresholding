import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class PrettyPrint {
   private int numRows; //image Head info
   private int numCols; //image Head info
   private int minVal;  //image Head info
   private int maxVal;  //image Head info
   private String outFile;
   private String inFile;
   
   public PrettyPrint(String[] args) throws IOException , FileNotFoundException {
      //Get the input/output filename;
      inFile=args[0];
      outFile=args[0]+"_PP.txt";
      msg("Start Reading Head info...");
      
      //Get the Head info from input file;
      Scanner sc;
      sc = new Scanner(new FileInputStream(inFile));
      if(!sc.hasNext()){
         System.out.println("Error, Empty input file.");
         sc.close();
         return;
      }else{
         numRows=sc.nextInt();
         numCols=sc.nextInt();
         minVal=sc.nextInt();
         maxVal=sc.nextInt();
      }
      sc.close();
      
      msg("Image size is " + numRows + "x" + numCols + ", " + "Grey-Scale Range is " + minVal + "-" + maxVal + ";");
   }

   public void prettyPrint()throws IOException, FileNotFoundException{
      msg("Start Reading Image...");
      Scanner sc;
      sc = new Scanner(new FileInputStream(inFile));
      if(!sc.hasNext()){
         System.out.println("Error, Empty input file.");
         sc.close();
         return;
      }else{
         String temp=sc.nextLine();
         msg(temp);
         
         int gVal=0;
         FileWriter fw = new FileWriter(outFile);
         fw.write(numRows+ " " + numCols + " " + minVal + " " + maxVal + "\r\n" );
         
         for (int i = 1; i < numRows + 1; i++) {
            for (int j = 1; j < numCols + 1; j++) {
               if(sc.hasNext()){
                  gVal=sc.nextInt();
               } 
               if (gVal > 0){
                  System.out.print(gVal+" ");
                  fw.write(gVal+" ");
               }else{
                  System.out.print("  ");
                  fw.write("  ");
               }
            }
            System.out.println("");
            fw.write("\r\n");
         }
         fw.close();
      
      }
      sc.close();
      msg("Finish Computation Threshold...");
   }

   public static void main (String[] args){
      try {
         if(args.length < 1){
             System.out.println("Run as : java PrettyPrint [inputFile1]");
             return;
         }

         PrettyPrint PP = new PrettyPrint(args);
         PP.prettyPrint();

       
      }catch (IOException e) {     
         e.getMessage();
         System.out.println(e.getMessage()+"     ~~~ Try again ~~~");
      }           
   }
   public static void msg(String m) {
      System.out.println("["+m+"]");   
   }
}
