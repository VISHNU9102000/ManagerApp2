<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<link rel="stylesheet" href="${pageContext.request.contextPath}/CSS/Home.css" />
<meta charset="ISO-8859-1">
<title>HOME</title>
</head>
<body style='align:center; background-color :#f1f1f1'>
<%
response.setHeader("Cache-Control", "no-cache, no-store, must-revalidate"); // HTTP 1.1.
response.setHeader("Pragma", "no-cache"); // HTTP 1.0.
response.setDateHeader("Expires", 0);
  if(session.getAttribute("Role")==null)
  {
	  response.sendRedirect("Login.jsp");
  }
   %> 
   <div class="topnav">
  <a class="active">Welcome ${username} </a>
  <a class="active" href="<%=request.getContextPath()%>/CollectData">ACTIVE DIRECTORY USER DATA</a>
  <a href="<%=request.getContextPath()%>/Logout" class="split">Logout</a>
</div>
<div id="one">
<h1 style="text-align:center;">CLICK TO VIEW TASK MANAGER</h1>
  <form style="text-align:center;" action="<%=request.getContextPath()%>/Welcome" method="Get">
  <input type="submit" class="button" value="CLICK HERE">
  </form>
 </div>
</body>
</html>