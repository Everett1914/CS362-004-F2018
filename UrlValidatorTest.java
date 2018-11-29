

import junit.framework.TestCase;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
      UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
      assertTrue(urlVal.isValid("http://www.google.com"));
      assertTrue(urlVal.isValid("http://www.google.com/"));
      assertTrue(urlVal.isValid("http://ftp.google.com"));
      assertTrue(urlVal.isValid("http://www.google.com/"));
      ArrayList<String> result = new ArrayList<>();
      
      try (BufferedReader br = new BufferedReader(new FileReader("urls.text"))) {
          while (br.ready()) {
              result.add(br.readLine());
          }
      }
      catch (IOException e) {
			e.printStackTrace();
      }
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
