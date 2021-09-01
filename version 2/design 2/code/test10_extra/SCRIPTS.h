/* Our Webpage needs SCRIPTS - this is them       */
/* main       - is script shared with most pages  */
/* management - is extra script used for the OTA  */

#ifndef SCRIPTS_h
#define SCRIPTS_h

const char CSS_SCRIPTS[] PROGMEM = R"rawliteral(


      function darkFunction() {
       var xhr = new XMLHttpRequest();
       xhr.open("GET", "/darkmode?state=1", true);
       xhr.send();
       setTimeout(function () {window.location.reload();}, 100);
      }

    
    

   function checkConnectionStatus()
   {
    let xhttp = new XMLHttpRequest();
    xhttp.timeout = 2000;
    xhttp.onreadystatechange = function()
    {
        if (this.readyState == 4)
        {
            if (this.status === 200)
            {
                document.getElementById("state").style.background = this.responseText;
            }
            else
            {
                document.getElementById("state").style.background = "red";
            }
             setTimeout(checkConnectionStatus, 5000);
            // Repeat our status check only once there's a result
        }
    }
    xhttp.open("GET", "/state", true);
    xhttp.send();
}
// Initial status check
setTimeout(checkConnectionStatus, 5000);

)rawliteral";


#endif
