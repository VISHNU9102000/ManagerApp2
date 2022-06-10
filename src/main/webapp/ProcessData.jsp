<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.*" %>
<!DOCTYPE html>
<html>
<head>
<title>TASK MANAGER</title>
<link rel="stylesheet" href="${pageContext.request.contextPath}/CSS/ProcessData.css" />
<script src="http://code.jquery.com/jquery-1.7.2.min.js" text="text/javascript"></script>
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <link href="http://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css" rel="stylesheet">   
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js"></script>
<link rel="stylesheet" 
href="http://cdn.datatables.net/1.10.2/css/jquery.dataTables.min.css"></link>
<script type="text/javascript" 
src="http://cdn.datatables.net/1.10.2/js/jquery.dataTables.min.js"></script>
<script type="text/javascript" 
src="http://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/js/bootstrap.min.js"></script>
<script>
    $(document).ready(function(){
        $('#myTable').dataTable();
    });
    </script>        
<title>DATA</title>
</head>
<body>
<%
response.setHeader("Cache-Control", "no-cache, no-store, must-revalidate"); // HTTP 1.1.
response.setHeader("Pragma", "no-cache"); // HTTP 1.0.
response.setDateHeader("Expires", 0);
  if(session.getAttribute("username")==null)
  {
	  response.sendRedirect("Login.jsp");
  }
   %>
   <%--navigation bar--%>
   <div class="topnav">
   <a href="<%=request.getContextPath()%>/Home.jsp" class="active">Home</a>
  <a class="active">Welcome ${username} </a>
  <a href="<%=request.getContextPath()%>/Logout" class="split">Logout</a>
</div>
<%--header--%>
<h1 style="text-align:center; padding:auto; background-color:DarkSlateGray; color:White">TASK MANAGER</h1>

<%--Refresh button--%>
<form style="text-align:center;" action="<%=request.getContextPath()%>/Welcome" method="GET">
  <input type="submit" class="button" value="REFRESH">
 </form>
<div>
<table id="myTable" class="table table-striped" >
<thead>
     <tr>
      <th>NAME</th>
      <th>ID</th>
      <th>MEMORY(Mb)</th>
      <th>CPU(in Sec)</th>
      <th>PATH</th>
      <%if(session.getAttribute("Role")=="Admin"){%>
      <th>END TASK</th>
      <%}
      else{%>
      <th></th>
      <%}%>
      </tr>
   </thead>
      <tbody>
    <%ArrayList<String> list = new ArrayList<>();
      list=(ArrayList<String>)request.getAttribute("data");
      for(int i=0;i<list.size();i++){%>
      <% String[] arr = list.get(i).split("\\s",5);
       if(arr.length==5 && arr!=null) {%>
	        <tr>
	          <td><%=arr[0]%></td>
	          <td><%=arr[1]%></td>
	          <td><%=arr[2]%></td>
	          <td><%=arr[3]%></td>
	          <td style="width:60%;"><%=arr[4]%></td>
	          <%if(session.getAttribute("Role")=="Admin"){%>
	                <td>
	              <a class="button" href="EndProcess?param=<%=arr[1]%>">EndTask</a>
	              </td>
	          <%}else{%>
	          <td></td>
	          <%}%>
	        </tr>
        <%}
       if(arr.length==4 && arr!=null){%>
	          <tr>
		          <td><%=arr[0]%></td>
		          <td><%=arr[1]%></td>
		          <td><%=arr[2]%></td>
		          <td><%=arr[3]%></td>
		          <td style="width:60%;"><% %></td>
	               <%if(session.getAttribute("Role")=="Admin"){%>
	                <td>
	              <a class="button" href="EndProcess?param=<%=arr[1]%>">EndTask</a>
	              </td>
	          <%}else{%>
	          <td></td>
	          <%}%>
		          
	          </tr>
	      <%}}%> 
	      </tbody>     
      </table>
     </div> 
</body>
</html>