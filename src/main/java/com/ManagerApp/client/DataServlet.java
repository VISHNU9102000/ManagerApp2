package com.ManagerApp.client;

import java.io.IOException;
import java.util.ArrayList;

import com.ManagerApp.handler.Linux;
import com.ManagerApp.handler.Windows;

import jakarta.servlet.RequestDispatcher;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
public class DataServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	public void doGet(HttpServletRequest req,HttpServletResponse res) throws IOException,ServletException,NullPointerException
	{
		HttpSession session=req.getSession(true); 
		 res.setHeader("Cache-Control", "no-cache, no-store, must-revalidate"); // HTTP 1.1.
		 res.setHeader("Pragma", "no-cache"); // HTTP 1.0.
		 res.setDateHeader("Expires", 0);
		  if(session.getAttribute("username")==null || session.getAttribute("Role")==null)
		  {
			  StringBuffer url = req.getRequestURL();
			  String URL = url.toString();
			  session.setAttribute("url", URL);
			  res.sendRedirect("Login.jsp");  
		  }
		  
		  else {
			res.setContentType("text/html");
			ArrayList<String> arr = new ArrayList<>();
			if(System.getProperty("os.name").contains("Windows"))
			{
				arr = Windows.value();
			}
			else if(System.getProperty("os.name").contains("Linux"))
			{
				arr = Linux.value();
			}
			req.setAttribute("data", arr);
			RequestDispatcher rd = req.getRequestDispatcher("ProcessData.jsp");
					rd.include(req, res);
			}
		  }
	}

