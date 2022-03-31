/**
 * Pagina HTML del porton del IAR 
 * 
 * */

const char INDEX_PAGE[] = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Control del porton</title>
   
<style>
.button {
  border: none;
  color: white;
  padding: 16px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  transition-duration: 0.4s;
  cursor: pointer;
}
.button2 {
  background-color: white; 
  color: black; 
  border: 2px solid #008CBA;
}

.button2:hover {
  background-color: #008CBA;
  color: white;
} 

</style>
</head>
<body>
<h1>Acceso portón </h1>
<button class="button button2" id="button_door" onclick = "myFunction()">Activar </button>
</body>
<script>
    function myFunction(){
        console.log("press") ;
        //document.getElementById('button_door')
        const Http = new XMLHttpRequest();
        const url='http://"ip_port"/open';
        Http.open("GET", url,true);
        Http.send();
        Http.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200){
                console.log(Http.responseText) ;
            }
        }
    }
</script>

</html>

)=====" ;