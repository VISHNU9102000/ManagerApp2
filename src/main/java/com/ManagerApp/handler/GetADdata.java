package com.ManagerApp.handler;

import java.util.ArrayList;

public class GetADdata
{
 static {
	 try {
		 System.load("C:\\FINAL_TASK\\apache-tomcat-10.0.13\\webapps\\ManagerApp\\headers&dlls\\ADUserDetail.dll");
		 System.load("C:\\FINAL_TASK\\apache-tomcat-10.0.13\\webapps\\ManagerApp\\headers&dlls\\ActiveDirectory_Data.dll");
		 }catch(UnsatisfiedLinkError e) {
	        System.err.println("Native code library failed to load.\n" + e);
	 }
   }
   public native ArrayList<String> GetData(String alert);
   public static void main(String[] args)
     {	 
    }
}
