<!DOCTYPE html>
<html>
<head>
<title>SIGN UP</title>
<link rel="stylesheet" href="${pageContext.request.contextPath}/CSS/Signup.css" />
 <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.8.3/jquery.min.js"></script>
 <script type="text/javascript" src="<%= response.encodeURL(request.getContextPath() + "/JavaScript/SignUp.js") %>" language="javaScript"></script>
</head>
<body>
<%
response.setHeader("Cache-Control", "no-cache, no-store, must-revalidate"); // HTTP 1.1.
response.setHeader("Pragma", "no-cache"); // HTTP 1.0.
response.setDateHeader("Expires", 0);
%>
  <div class="container">
    <h1>Sign Up</h1>
    <p>Please fill in this form to create an account.</p>
    <span style='color:red' id='exist'></span>
    <hr>
    <label for="username"><b>USERNAME</b></label>
    <input type="text" placeholder="USERNAME" name="username" id="username" required>

    <label for="psw"><b>PASSWORD</b></label>
    <input type="password" placeholder="ENTER PASSWORD" name="password" id="password" required>

    <label for="psw-repeat"><b>REPEAT PASSWORD <span id='message'></span></b></label>
    <input type="password" placeholder="REPEAT PASSWORD" name="psw-repeat" id="confirmpassword" required>
    
    <label>
      <input type="checkbox" name="rem" value="1"/> Remember Me <br>
      </label>
    <button type="button" onclick="signup()">SIGN UP</button>
    </div>
    <div class="container" style="background-color:#f1f1f1">
  <a class="button" href="<%=request.getContextPath()%>/Login.jsp">CANCEL</a>
  </div>
</body>
  