<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    <%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<link rel="stylesheet" href="${pageContext.request.contextPath}/CSS/PrintUserData.css" />
<title>	AD DATA</title>
</head>
<body>
<div class="topnav">
  <a href="<%=request.getContextPath()%>/Home.jsp" class="active">Home</a>
  <a class="active">Welcome ${username} </a>
  <a href="<%=request.getContextPath()%>/Logout" class="split">Logout</a>
    </div>
  <h1 style="text-align:center; padding:auto; background-color:DarkSlateGray; color:White">	ACTIVE DIRECTORY USERS DATA </h1>
  <div>
  <table>
    <tbody>
    <%ArrayList<String> list = new ArrayList<>();
      list=(ArrayList<String>)request.getAttribute("data");
      for(int i=0;i<list.size();i++){%>
      <% String[] arr = list.get(i).split("\n");
       {%>    
	          <tr><h1 style="background-color:Grey;"><%=arr[0]%></h1></tr>
	          <%for(int j=1;j<arr.length;j++){ %>
	          <tr><h3><%=arr[j]%></h3></tr>
        <%}}}%> 
	      </tbody>
   </table>
</div>
</body>
</html>