import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Histogram {
   private int histogram[];
   private int numRows;
   private int numCols;
   private int minVal;
   private int maxVal;
   private String outFile;
   private String inFile;
   
   public Histogram(String[] args) throws FileNotFoundException {
      //Get the output filename;
      outFile=args[1];
      inFile=args[0];
   }
   public void computeHistogram()throws FileNotFoundException{
      msg("Start Reading Image...");
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
         
         msg("Image size is " + numRows + "x" + numCols + ", " + "Grey-Scale Range is " + minVal + "-" + maxVal + ";");
         //Initialize Histogram Array 
         histogram = new int[maxVal+1];
         for (int i = 0; i< maxVal+1; i++) {
            histogram[i]=0;
         }
         while (sc.hasNext()) {
            histogram[sc.nextInt()]++;
         }
      }
      sc.close();
      msg("Finish Computation Histogram.");
   }
   public void printHistogram()throws IOException{
      FileWriter fw = new FileWriter(outFile);
      fw.write("Image size is " + numRows + "x" + numCols + ", " + "Grey-Scale Range is " + minVal + "-" + maxVal + ";" + "\r\n");
      for(int i=0; i<maxVal+1; i++){
         System.out.print("("+i+"):"+histogram[i]+" ");
         fw.write("("+i+"):"+histogram[i]+" ");
         if (histogram[i]>0){
            int limit=histogram[i];
            if (limit>80){limit=80;}
            for(int j=0; j<limit; j++){
               System.out.print("+");
               fw.write("+");
            }
            System.out.println("");
            fw.write("\r\n");
         }
         else{
            System.out.println("");
            fw.write("\r\n");
         }
      }
      fw.close();
   }
     
   public static void main (String[] args){
      try {
         if(args.length < 2){
             System.out.println("Run as : java Histogram [inputFile1] [outputFile1] ");
             return;
         }

         Histogram HG = new Histogram(args);
         HG.computeHistogram();
         HG.printHistogram();
       
      }catch (IOException e) {     
         e.getMessage();
         System.out.println(e.getMessage()+"     ~~~ Try again ~~~");
      }           
   }
   public static void msg(String m) {
      System.out.println("["+m+"]");   
   }
}
