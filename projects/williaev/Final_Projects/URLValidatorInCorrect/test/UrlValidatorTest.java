

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   //UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   UrlValidator urlVal = new UrlValidator();
	   System.out.println("Manual Test: Valid URLs");
	   String[] urlsVal = {"http://www.google.com:80/test1/", "http://foo.com/blah_blah","https://userid:password@example.com:8080", 
			   "ftp://www.foo.bar/", "http://go.com:80/test1?action=view", "http://go.com:80/test1?action=edit&mode=up",
			   "http://go.com:80/test1",
			   "http://go.com:80/t123?action=view",
			   "http://go.com:80/t123?action=edit&mode=up",
			   "http://go.com:80/t123",
			   "http://go.com:80/$23?action=view",
			   "http://go.com:80/$23?action=edit&mode=up",
			   "http://go.com:80/$23"};
	   for(int i = 0; i < urlsVal.length; i++) {
		   assertTrue(urlVal.isValid(urlsVal[i]));
	   }
	   System.out.println("Test For Valid URLs Complete");
	   System.out.println("Manual Test: Invalid URLs");
	   String[] urlsInVal = {"http://",
			   "http://.",
			   "http://..",
			   "http://../",
			   "http://?",
			   "http://??",
			   "http://??/",
			   "http://#",
			   "http://##",
			   "http://##/",
			   "http://foo.bar?q=Spaces should be encoded"};
	   for(int i = 0; i < urlsInVal.length; i++) {
		   assertFalse(urlVal.isValid(urlsInVal[i]));
	   }
	   System.out.println("Test For Invalid URLs Complete");
   }
   
   
   public void testYourFirstPartition()
   {
	   UrlValidator urlVal = new UrlValidator();
	   System.out.println("Authority Partition Testing For Valid URLs");
	   assertTrue(urlVal.isValid("http://amazon.com:80"));
	   assertTrue(urlVal.isValid("http://go.com/$23"));
	   assertTrue(urlVal.isValid("http://go.au:80/"));
	   assertTrue(urlVal.isValid("http://0.0.0.0:65535"));
	   System.out.println("Authority Partition Testing For Valid URLs Complete");
	   UrlValidator urlInVal = new UrlValidator();
	   System.out.println("Authority Partition Testing For Valid URLs");
	   assertFalse(urlInVal.isValidAuthority("aaa."));
	   assertFalse(urlInVal.isValid("://255.com:80/$23"));
	   assertFalse(urlInVal.isValidAuthority("://255.com:-1"));
	   assertFalse(urlInVal.isValid("go.a1a"));
	   System.out.println("Authority Partition Testing For Invalid URLs Complete");

   }
   
   public void testYourSecondPartition(){
	   UrlValidator urlVal = new UrlValidator();
	   System.out.println("Path Testing For Valid URLs");
	   assertTrue(urlVal.isValid("http://0.0.0.0:80/t123?action=edit&mode=up"));
	   assertTrue(urlVal.isValid("ftp://255.com/t123"));
	   assertTrue(urlVal.isValidPath("/test1"));
	   assertTrue(urlVal.isValidPath("/$23"));
	   System.out.println("Authority Partition Testing For Valid URLs Complete");
	   UrlValidator urlInVal = new UrlValidator();
	   System.out.println("Authority Partition Testing For Valid URLs");
	   assertFalse(urlInVal.isValid("://255.com:65636/../"));
	   assertFalse(urlInVal.isValid("://255.com:-1/.."));
	   assertFalse(urlInVal.isValidPath("/..//file"));
	   assertFalse(urlInVal.isValidPath("/.."));
	   System.out.println("Authority Partition Testing For Invalid URLs Complete");	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }

}
