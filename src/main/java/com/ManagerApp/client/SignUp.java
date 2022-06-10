package com.ManagerApp.client;


import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

import org.json.simple.JSONObject;

import com.ManagerApp.handler.LoginBean;
import com.ManagerApp.handler.LoginDao;
public class SignUp extends HttpServlet {
	private static final long serialVersionUID = 1L;
    //private static final long serialVersionUID = 1 L;
    private LoginDao loginDao;
    public void init() {
        loginDao = new LoginDao();
    }
	@SuppressWarnings("unchecked")
	protected void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException
	{
		boolean status = false;
		System.out.println("Entering into SignUp.java");
		String msg = null;
		PrintWriter out = res.getWriter();
		JSONObject object1 = new JSONObject();
		String username = req.getParameter("username");
        String password = req.getParameter("password");
        LoginBean loginBean = new LoginBean();
        loginBean.setUsername(username);
        loginBean.setPassword(password);
        try {
        	status = loginDao.CheckUser(loginBean);
		} catch (ClassNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
        if(status)
        {
        	msg="1";
        }
        else
        {
					try {
						if(loginDao.CreateUser(loginBean))
						{
							System.out.println("User created successfully");
							msg="3";
				             
				        } 
				        else {
				        	msg="2";
				        }
				      }catch (ClassNotFoundException e) {
				        e.printStackTrace();
				      }
        }
               object1.put("msg",msg);
			   System.out.println(msg);
	           System.out.println(object1);
	        
	           out.println(object1);
	           out.flush();
	        System.out.println(msg);
   }	
}
