package com.ManagerApp.client;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
public class EndProcess extends HttpServlet {
	private static final long serialVersionUID = 1L;
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		 String id = (String)request.getParameter("param");
		 System.out.println(id);
		  
			try{
				String end;
				if(System.getProperty("os.name").contains("Windows"))
				{	
					 end  = "powershell.exe Stop-process -Id "+id;
				}
				else
				{
					end = "kill -15 "+id;
				}
			    
			     Process pd = Runtime.getRuntime().exec(end);
				Thread.sleep(2000);
			     response.sendRedirect("Welcome");
			     }catch(Exception e)
			     {
			         e.printStackTrace();
			     }
	}

}
