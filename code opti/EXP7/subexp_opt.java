/*
                                                NAME: PATEL MUSKAN KASIM SHAH.
                                                ROLL NO: 22DCO04
                                                BATCH: 01
                                                SEMESTER: 6
                                                DATE: 21-03-2024
                                                
                                                
                           EXPERIMENT 4
            AIM: IMPLEMENTATION OF CODE OPTIMIZATION.
            
*/




import java.io.*;
import java.util.*;
class subexp_opt
{
 public static void main(String args[])throws IOException
 {
 String s,temp;
 String arr[][]=new String[10][2]; //assuming 10 unique operations with LHS and RHS stored
 int flag=0,index=0;
 BufferedReader br=new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
 File op = new File("output.txt");
 if (!op.exists())
 op.createNewFile();
 BufferedWriter output = new BufferedWriter(new FileWriter(op.getAbsoluteFile()));
 for(;(s=br.readLine())!=null;flag=0)
 {
 temp=s.substring(s.indexOf("=")+1);
 for(int i=0;i<index;i++)
 {
 if(temp.equals(arr[i][1])) 
 {
 flag=1;
 break;
 }
 else if(temp.contains(arr[i][1]))
 s=s.replaceAll(arr[i][1],arr[i][0]);
 } 
 if(flag==0)
 {
 arr[index][0]=s.substring(0,s.indexOf("="));
 arr[index][1]=temp;
 index++;
 output.write(s);
 output.newLine();
 }
 }
 output.close();
 }
}
