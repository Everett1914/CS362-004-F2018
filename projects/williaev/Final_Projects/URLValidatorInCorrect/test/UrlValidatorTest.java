
import junit.framework.TestCase;



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
			   "://256.256.256.256/test1/",
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
	   System.out.println("Manual Test: Invalid and Valid URLs");
	   String[] urlsMix = {"http://",
			   "://256.256.256.256/test1/",
			   "http://..",
			   "http://../",
			   "http://?",
			   "http://??",
			   "http://??/",
			   "http://#",
			   "http://##",
			   "http://##/",
			   "http://foo.bar?q=Spaces should be encoded"};
	   for(int i = 0; i < urlsMix.length; i++) {
		   assertFalse(urlVal.isValid(urlsMix[i]));
	   }
	   System.out.println("Test For Mixed(valid/invalid) URLs Complete");
   }
   
    public void testIsValidScheme(UrlValidator uv, String[] scheme, boolean expected, String msg) {
	   for(int i = 0 ; i < scheme.length; i++) {
		   try {
				 assertEquals(expected, uv.isValidScheme(scheme[i]));
		   }catch(Error e) {
			   System.err.println("FAILURE " + msg + ":\n" + scheme[i] + " caused an error.");
			   System.err.print(e.getMessage());
			   System.err.println("\n");

		   }
	   }

   }

   public void testIsValidAuthority(UrlValidator uv, String[] authority, boolean expected, String msg) {
	   for(int i = 0 ; i < authority.length; i++) {
		   try {
				 assertEquals(expected, uv.isValidAuthority(authority[i]));
		   }catch(Error e) {
			   System.err.println("FAILURE " + msg + ":\n" + authority[i] + " caused an error.");
			   System.err.print(e.getMessage());
			   System.err.println("\n");

		   }
	   }

   }

   public void testIsValidPath(UrlValidator uv, String[] path, boolean expected, String msg) {
	   for(int i = 0 ; i < path.length; i++) {
		   try {
				 assertEquals(expected, uv.isValidPath(path[i]));
		   }catch(Error e) {
			   System.err.println("FAILURE " +msg+ ":\n" + path[i] + " caused an error.");
			   System.err.print(e.getMessage());
			   System.err.println("\n");
		   }
	   }
   }

   
   public void testIsValidQuery(UrlValidator uv, String[] query, boolean expected, String msg) {
	   for(int i = 0 ; i < query.length; i++) {
		   try {
				 assertEquals(expected, uv.isValidQuery(query[i]));
		   }catch(Error e) {
			   System.err.println("FAILURE " +msg+ ":\n" + query[i] + " caused an error.");
			   System.err.print(e.getMessage());
			   System.err.println("\n");
		   }
	   }
   }
   
   public void testIsValid(UrlValidator uv, String url, boolean expected) {
		   try {
				 assertEquals(expected, uv.isValid(url));
		   }catch(Error e) {
			   System.err.println("FAILURE TESTING isValid:\n" + url + " caused an error.");
			   System.err.print(e.getMessage());
			   System.err.println("\n");
		   }
   }
   
   // don't look to junit for failures, look at the console. try catch blocks will catch the assert errors
   public void testPartitions()
   {
	   String[] allowedSchemes = {"hello", "world"};
	   String[] badSchemes = {"foo" , "bar"};
	   String[] defaultSchemes = {"http", "https", "ftp"};

	   UrlValidator allowAllSchemes = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   UrlValidator uvAllowSomeSchemes = new UrlValidator(allowedSchemes, null, 0);
	   UrlValidator uvAllowDefaultSchemes = new UrlValidator(null, null, 0);
	      
	   // allowallschemes should accept all of these
	   testIsValidScheme(allowAllSchemes, allowedSchemes, true, "allow all schemes should always return true");
	   testIsValidScheme(allowAllSchemes, badSchemes, true, "allow all schemes should always return true");
	   testIsValidScheme(allowAllSchemes, defaultSchemes, true, "allow all schemes should always return true");
	   
	   //allowsomeschemes should allow only the specific ones
	   testIsValidScheme(uvAllowSomeSchemes, allowedSchemes, true, "allow some schemes should allow specificed schemes");
	   testIsValidScheme(uvAllowSomeSchemes, badSchemes, false, "allow some schemes should disallow made up schemes");
	   testIsValidScheme(uvAllowSomeSchemes, defaultSchemes, false, "allow some schemes should disallow default schemes");
	   
	   //allowdefaultschemes should allow only the default ones
	   testIsValidScheme(uvAllowDefaultSchemes, allowedSchemes, false, "allow default schemes allows only default schemes");
	   testIsValidScheme(uvAllowDefaultSchemes, badSchemes, false, "allow default schemes allows only default schemes");
	   testIsValidScheme(uvAllowDefaultSchemes, defaultSchemes, true, "allow default schemes should allow default schemes");
	   
	   String[] validAuthority = {"www.google.com", "www.google.com:80", "255.255.255.255"};
	   String[] invalidAuthority = {null, "www.a" , "www.google.com::80", "256.256.256.256","255.255.255.255.255", "-1.-1.-1.-1"};
	   
	   testIsValidAuthority(allowAllSchemes, validAuthority, true, "giving valid authority to isValidAuthority");
	   testIsValidAuthority(allowAllSchemes, invalidAuthority, false, "giving invalid authority to isValidAuthority");
	   
	   
	   String[] validPath = {"", "/", "/help", "/hello/world"};
	   String[] invalidPath = {"//" , ".."};

	   testIsValidPath(allowAllSchemes, validPath, true, "giving valid paths to isValidPath");
	   testIsValidPath(allowAllSchemes, invalidPath, false, "giving invalid paths to isValidPath");
	  
	   String[] validQuery = {"", "?search=cats", "?time=1200&date=20180101", null};
	   String[] invalidQuery = {"???", "?hello"};

	   testIsValidQuery(allowAllSchemes, validQuery, true, "giving valid input given to isValidQuery");
	   testIsValidQuery(allowAllSchemes, invalidQuery, false, "giving invalid input to isValidQuery");
   }

   
  public void testIsValid() {

	  String[] allowedSchemes = {"hello", "world"};
	  
	  ResultPair[] allowAllSchemesTested = {
			  new ResultPair("hello", true),		 
			  new ResultPair("world", true),		 
			  new ResultPair("foo", true),		 
			  new ResultPair("bar", true),		 
			  new ResultPair("http", true),		 
			  new ResultPair("ftp", true),		 
			  new ResultPair("file", true),		 
			  };
	  
	  ResultPair[] allowSomeSchemesTested = {
			  new ResultPair("hello", true),		 
			  new ResultPair("world", true),		 
			  new ResultPair("foo", false),		 
			  new ResultPair("bar", false),		 
			  new ResultPair("http", false),		 
			  new ResultPair("ftp", false),		 
			  new ResultPair("file", false),		 
			  };

	  ResultPair[] allowDefaultSchemesTested = {
			  new ResultPair("hello", false),		 
			  new ResultPair("world", false),		 
			  new ResultPair("foo", false),		 
			  new ResultPair("bar", false),		 
			  new ResultPair("http", true),		 
			  new ResultPair("ftp", true),		 
			  new ResultPair("file", false),		 
			  };

	   UrlValidator[] uvs = {
			   new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES),
			   new UrlValidator(allowedSchemes, null, 0),
			   new UrlValidator(null, null, 0)
	   };
	   
	   ResultPair[] schemeDelimitersTested = {
			 new ResultPair ("://", true),
			 new ResultPair ("//", false),
			 new ResultPair (":/", false),		 
	   };
	   
	   ResultPair[] authoritiesTested = {
			new ResultPair("www.google.com", true),		 
			new ResultPair("www.google.com:80", true),		 
			new ResultPair("foo", false),		 
			new ResultPair("bar", false),		 
			new ResultPair("255.255.255.255", true),		 	 
			new ResultPair("www.google.cm", false),
			new ResultPair("www.google.com::80", false),
			new ResultPair("256.256.256.256", false),		 
			new ResultPair("255.255.255.255.255", false)	 
		};
	   	   
	   ResultPair[] pathsTested = {
			new ResultPair("", true),		 
			new ResultPair("/", true),
			new ResultPair("/search", true),
			new ResultPair("/hello/world", true),		 		 		 
			new ResultPair("/..", false),
	   };
	   
	   ResultPair[] queriesTested = {
			new ResultPair("", true),		 
			new ResultPair("?q=cats", true),		 
			new ResultPair("?time=1200&date=20180101", true),		 
			new ResultPair("???", false),		 
			new ResultPair("?hello world", false),	 
	   };

	   StringBuilder url = new StringBuilder();
	   boolean expected;
	   UrlValidator currentValidator;
	   ResultPair[] currentSchemes;
	   for(int i = 0 ; i < uvs.length; i++) {
		   currentValidator = uvs[i];
		   if(i == 0) {
			   currentSchemes = allowAllSchemesTested;
		   }
		   if(i == 1) {
			   currentSchemes = allowSomeSchemesTested;
		   }
		   else {
			   currentSchemes = allowDefaultSchemesTested;
		   }
		   
		   for(int j = 0; j < currentSchemes.length; j++) {
			   expected = true;
			   if(!currentSchemes[j].valid) {
				   expected = false;
			   }
			   
			   for(int k = 0; k < schemeDelimitersTested.length; k++) {
				   if(!schemeDelimitersTested[k].valid) {
					   expected = false;
				   }
				   
				   for(int m = 0; m < authoritiesTested.length; m++) {
					   if(!authoritiesTested[m].valid) {
						   expected = false;
					   }
						   
					   for(int x = 0; x < pathsTested.length; x++) {
						   if(!pathsTested[x].valid) {
							   expected = false;
						   }
							   
						   for(int y = 0; y < queriesTested.length; y++) {
							   url.setLength(0);
							   url.append(currentSchemes[j].item);
							   url.append(schemeDelimitersTested[k].item);
							   url.append(authoritiesTested[m].item);
							   url.append(pathsTested[x].item);
							   url.append(queriesTested[y].item);
							  if(!queriesTested[y].valid) {
								   expected = false;
							   }
							   testIsValid(currentValidator, url.toString(), expected);
						   }
					   }
				   }
			   }
		   }
	   }
  	}
  }


