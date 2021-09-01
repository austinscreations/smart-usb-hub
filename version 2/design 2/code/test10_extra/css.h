/* Our webpage needs style - This CSS helps with that */

#ifndef css_h
#define css_h

const char CSS_STYLE[] PROGMEM = R"rawliteral(
    <style>
    
     %dark%

     body {
   margin:0;
   padding:0;
}
#container {
   position:relative;
   min-height: 100%%;
}
#header {
   padding:00px;
}
#body {
  padding-bottom: 100px;
}
#footer {
   height:100px;   /* Height of the footer */
   position:absolute;
   bottom:0;
   width:100%%;
}
 #midcontent {
        left: 0;
        line-height: 200px;
        margin-top: -100px;
        position: absolute;
        text-align: center;
        top: 50%;
        width: 100%;
      }

   html {font-family: Arial; display: inline-block; text-align: center;}
   h2 {
    font-size: 3.0rem;
    color: %color%;
    margin-bottom: 0.4rem;
   }
   .menu-buttons{
     margin-top: 1.0rem;
     margin-bottom: 1.0rem;
   }    
   .buttons {
     border: .15rem solid;
     border-radius: .4rem;
     font-weight: bold;
     padding: .25rem .6rem;;
     text-align: center;
     text-decoration: none;
     display: inline-block;
     font-size: 1.0rem;
     margin: .5rem .5rem .5rem .5rem;;
     cursor: pointer;
   }
   .ButtonHere {
    background-color: %color%;
    border-color: %hover%;
    color: White;
   } 
   .ButtonClickable:hover {
    background-color: %hover%;
    color: white;
   }

   .border{
    border: 0.25rem solid %color%;
    border-radius: .4rem;
    width: 30rem;
    margin: auto;
    padding:  .4rem;
    }

    .name-status {
     border-radius: .4rem;
     font-weight: bold;
     padding: .25rem .6rem;
     display: inline-block;
     margin-bottom: 1rem;
    }

    .name-text {
    font-size: 1.2rem;
    font-weight: bold;
    }
  
   .label2{
    font-weight: bold;
    line-height: 1.2rem;
    min-height: 1.4rem;
    padding: .1rem .4rem .1rem 1.2rem;
    position: center;
    font-size: 1.25rem;
   }
  .pt-2 {padding-top: .75rem;}
  .form-input {
    margin-bottom: 1rem;
    background-image: none;
    border: 0.25rem dashed %hover%;
    border-radius: .4rem;
    color: %color%;
    font-size: 1rem;
    padding:  .4rem;
   }
     
   input[type="submit"] {
    background-color: %color%;
    color: white;
    font-size: 1.0rem;
    font-weight: bold;
    border:  .25rem solid %color%;
    border-radius: .4rem;
    padding:  .3rem .8rem;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    margin: .9rem .45rem .4rem .4rem;
    cursor: pointer;
   }
   input[type="submit"]:hover {
    background-color: #ffffff;
    border-color: #000000;
    color: %color%;
    border: .25rem solid;
    border-radius: .4rem;
    font-weight: bold;
    font-size: 1.0rem;
    cursor: pointer;
   }

   .col-4{
    border: 0.25rem solid %color%;
    border-radius: .4rem;
    width: 30rem;
    margin-top: 2rem;
    margin: auto;
    padding:  .4rem;
   }

   .w3-background{
    background-color: %hover%;
    border-radius: .4rem;
   }
  
   .w3-progress{
    color: #ffffff;
    background-color: %color%;
    border-radius: .4rem;
    text-align:center;
    padding: .6rem .6rem .6rem .6rem;
   }

   .upload-bar{
    background-image: none;
    border: 0.25rem dashed %hover%;
    border-radius: .4rem;
    padding: 0.3rem 0.6rem 0.3rem 0.6rem;
    margin: auto;
    width: 26rem;
   }

   .mt-4 {
    margin-top: 0.15rem;
   }
   .label {
    font-size: 1.0rem;;
   }
   .label.label-primary {
    background: %color%;
    color: #fff;
    margin-left: .5rem;
    margin-right: .5rem;
    font-size: 1.0rem;
   }
   .label.label-rounded {
    border-radius: 5rem;
    padding-left: .5rem;
    padding-right: .5rem;
    font-size: 1.0rem;
   }

    .mt-8 {
    margin-top: 5px;
    }
   
   .label.label-error {
    background: %color%;
    color: #fff;
    padding-left: 10rem;
    padding-right: 10rem;
   }
   
   .mt-10 {
    margin-top: 5px;
    }
    
   .label.label-blank {
    background: %color%;
    color: #fff;
    padding-left: 10rem;
    padding-right: 10rem;
   }
   
    .column3 {
     font-weight: bold;
     padding: 0.4rem;
     display: inline-block;
     font-size: 1.0rem;
     text-align:right;
    }
    
    .column4 {
     width: 4.8rem;
     font-weight: bold;
     padding: 0.4rem;
     display: inline-block;
     font-size: 1.0rem;
     text-align:left;
    }

   .status {
     border: .5rem solid;
     border-radius: .8rem;
     display: inline-block;
     font-weight: bold;
     padding: 0.1rem;
    }
    
    .outer {
     border: .2rem solid;
     border-radius: .8rem;
     display: inline-block;
     margin: .5rem;
     padding: 0.1rem;
    }
    
    .inner {
     width: 11rem;
     border: .2rem solid;
     border-radius: .4rem;
     display: inline-block;
    }

   input:invalid {
    border: 2px dashed red;
   }
   input:invalid:focus {
    background-color: #ffcccb;
   }

  </style>
)rawliteral";

#endif
