var msg=null;
 function login()
 {
	  var username = $("#username").val();
	  var password = $("#password").val();
	  var rem = $("#rem").prop('checked');
	  //alert(rem);
	  //string returnString = "";
	  //returnString = Convert.ToString(Session["url"]);
	  $.ajax({
		  url:"login",
		  type:"post",
		  data:{username:username,password:password,rem:rem},
		  success: function(responseText)
		  {
			  var a=JSON.parse(responseText)
			  var b=a["msg"];
				   
				   if(b=="0")
					   {
					    $('#message').html("Username or password incorrect");
					   }
				   else if(b=="1")
					   {
					      //alert("Hello"+ username);
					      window.location.href="Home.jsp";
					   }
				   else
					   {
					   var session =b;
					   session.replaceAll('/',"");
					   alert(session);
					   window.location.href=session;
					   }
		  }
	  })
  }