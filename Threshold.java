import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Threshold {
   private int thr_Ary[][];
   private int numRows; //image Head info
   private int numCols; //image Head info
   private int minVal;  //image Head info
   private int maxVal;  //image Head info
   private int thr_Val; // user input value
   private String outFile;
   private String inFile;
   
   public Threshold(String[] args) throws IOException , FileNotFoundException {
      //Get the output filename;
      inFile=args[0];
      msg("Start Reading Head Info...");
      
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
      
      //initialize thr_Ary;
      thr_Ary= new int[numRows+1][numCols+1];
      for (int i = 0; i < numRows + 1; i++) {
         for (int j = 0; j < numCols + 1; j++) {
             thr_Ary[i][j] = 0;
         }
      }
      
      //Get user input value
      readInput();
      
      //Generate output file name
      outFile="thr_"+thr_Val+".txt";
   }
   private void readInput() throws IOException {   
      Scanner sc;
      while(true){
         System.out.print("Please enter your threshold Value (" + minVal + "-" + maxVal + ") : ");
         sc = new Scanner(System.in);
         thr_Val=sc.nextInt();
         if (thr_Val >= minVal && thr_Val <= maxVal) {
            sc.close();
            break;
         }
         msg("Input out of range!!!");
      }
   }
   public void computeThreshold()throws FileNotFoundException{
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
         msg("Image size is " + numRows + "x" + numCols + ", " + "Grey-Scale Range is " + minVal + "-" + maxVal + ";");
         
         int gVal;
         for (int i = 1; i < numRows + 1; i++) {
            for (int j = 1; j < numCols + 1; j++) {
               if(sc.hasNext()){
                  gVal=sc.nextInt();
               } 
               else{
                  break;
               }
               if (gVal < thr_Val){
                  thr_Ary[i][j] = 0;
               }else{
                  thr_Ary[i][j] = 1;
               }
            }
         }
      }
      sc.close();
      msg("Finish Computation Threshold...");
   }
   public void printThreshold()throws IOException{
      FileWriter fw = new FileWriter(outFile);
      fw.write(numRows+ " " + numCols + " " + minVal + " " + maxVal + "\r\n" );
      for (int i = 1; i < numRows + 1; i++) {
         for (int j = 1; j < numCols + 1; j++) {
            System.out.print(thr_Ary[i][j]+" ");
            fw.write(thr_Ary[i][j]+" ");
         }
         System.out.println("");
         fw.write("\r\n");
      }
      fw.close();
   }
     
   public static void main (String[] args){
      try {
         if(args.length < 1){
             System.out.println("Run as : java Threshold [inputFile1]");
             return;
         }

         Threshold TH = new Threshold(args);
         TH.computeThreshold();
         TH.printThreshold();

       
      }catch (IOException e) {     
         e.getMessage();
         System.out.println(e.getMessage()+"     ~~~ Try again ~~~");
      }           
   }
   public static void msg(String m) {
      System.out.println("["+m+"]");   
   }
}
