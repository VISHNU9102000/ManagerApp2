package com.ManagerApp.client;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import org.json.simple.JSONObject;

import com.ManagerApp.handler.LoginBean;
import com.ManagerApp.handler.LoginDao;

import java.io.IOException;
import java.io.PrintWriter;

public class LoginServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	 private LoginDao loginDao;
	    public void init() {
	        loginDao = new LoginDao();
	    }
   
	@SuppressWarnings("unchecked")
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException 
	{
		String msg;
		PrintWriter out = response.getWriter();
		JSONObject object1 = new JSONObject();
		/*json data end*/
		String username = request.getParameter("username");
        String password = request.getParameter("password");
        String remember = request.getParameter("rem");
        System.out.println(username);
        System.out.println(password);
        System.out.println(remember);
        LoginBean loginBean = new LoginBean();
        loginBean.setUsername(username);
        loginBean.setPassword(password);
        HttpSession session = request.getSession();
        String link=null;
        link = (String) session.getAttribute("url");
        try {
            if (loginDao.validate(loginBean)) 
            {
            	System.out.println("Validation done");
            	session.setAttribute("username",username);
                boolean remember1 = request.getParameter("rem") != null;
                System.out.println( "Remeber me status : "+remember1);
                if (request.getParameter("rem").equals("true")) 
                {
					Cookie checkuser = new Cookie("Cookuname", username);
					checkuser.setMaxAge(5000);
					response.addCookie(checkuser);
					Cookie checkpswd = new Cookie("Cookpass", password);
					checkpswd.setMaxAge(5000);
					response.addCookie(checkpswd);
					Cookie ckReme = new Cookie("CookRem", remember);
					ckReme.setMaxAge(5000);
					response.addCookie(ckReme);
					
                    session.setAttribute("username",username);
                    if(loginDao.Role(loginBean))
                    {
                	   System.out.println("Hello Administrator yes cache");
                	   session.setAttribute("Role", "Admin");
                    }
                	else 
                    {
                   	   System.out.println("Hello User yes cache");
                   	   session.setAttribute("Role", "User");
                    }
                } else {
            	  if(loginDao.Role(loginBean))
                   {
            	      System.out.println("Hello Administrator no cache");
            	      session.setAttribute("Role", "Admin");
                   }
            	   else 
                   {
               	   System.out.println("Hello User no cache");
               	   session.setAttribute("Role", "User");
                   }
                 }
                 if(link==null)
        	      {
        	   	     msg="1";
        		     object1.put("msg",msg);
        	     }
                 else
       	         {
       		         msg=link;
       		         object1.put("msg",msg);
       	          }
                
                 
            } 
            else {
            	msg="0";
            	object1.put("msg",msg);
            }
            System.out.println(msg);
            System.out.println(object1);
            
            out.println(object1);
            out.flush();
            System.out.println(msg);
        }catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
		
		
	}

}
