var msg = null;
function signup() {
	var username = $("#username").val();
	var password = $("#password").val();
	$.ajax({
		url: "SignUp",
		type: "post",
		data: { username: username, password: password},
		success: function (responseText) {
			//alert(responseText);
			var a = JSON.parse(responseText);
			//alert(a);
			var b = a["msg"];
			//alert(b);

			if (b == "1") {
				$('#exist').html("Username already exists");
			}
			else if (b == "2") {
				$('#exist').html("Could not create account");
			}
			else if (b == "3") {
				window.location.href = "Login.jsp";
			}

		}
	})
}