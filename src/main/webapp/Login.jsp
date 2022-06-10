<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>   
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="${pageContext.request.contextPath}/CSS/Login.css" />
<script type="text/javascript" src="<%= response.encodeURL(request.getContextPath() + "/JavaScript/Login.js") %>" language="javaScript"></script>
<title>LOGIN</title>
</head>
<body>
<div id="dvBrowserDetails"></div>
<%
response.setHeader("Cache-Control", "no-cache, no-store, must-revalidate"); // HTTP 1.1.
response.setHeader("Pragma", "no-cache"); // HTTP 1.0.
response.setDateHeader("Expires", 0);
response.setDateHeader("Expires",-1);
String uname = "", password = "", remember = "";
Cookie[] cookies = request.getCookies();
if (cookies != null) {
	for (Cookie cook : cookies) {
		if (cook.getName().equals("Cookuname"))
	uname = cook.getValue();
		else if (cook.getName().equals("Cookpass"))
	password = cook.getValue();
		else if (cook.getName().equals("Cookrem"))
	remember = cook.getValue();
	}
}
if(session.getAttribute("Role")!=null)
{
	  response.sendRedirect("Home.jsp");
}
%>
<form name="form-login" id="form-login">
  <h1 style="text-align:center">WELCOME USER</h1>
  <div class="imgcontainer">
    <img src="${pageContext.request.contextPath}/images/UserLogo.jpg" alt="User" class="user">
  </div>
  <div class="container">
    <label for="uname"><b>USERNAME</b></label>
    <input type="text" id="username" name="username" placeholder="username"
			value="<%=uname%>" required />

    <label for="psw"><b>PASSWORD</b></label>
    <input type="password" name="password" id="password" placeholder="password" value="<%=password%>" required />
    <div style='color:red' id="message"></div>
    <label>
      <input type="checkbox" name="rem" id="rem"
			<%="1".equals(remember) ? "checked='/checked'" : " "%> /> RememberMe <br>
    </label>
    <button type="button" onclick="login()">LOGIN</button>
  </div>
</form>
  <div class="container" style="background-color:#f1f1f1">
  <a class="button" href="<%=request.getContextPath()%>/Signup.jsp">SIGNUP</a>
    <span class="psw">Forgot <a href="#">password?</a></span>
  </div>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script> 
</body>
</html>