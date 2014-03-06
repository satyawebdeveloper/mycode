<?php
/*
 * Class PayFlow
 */

class PayFlow {
	
	//Vendor Credentials
	public $USER;
	public $VENDOR;
	public $PARTNER;
	public $PWD;
	
	
	//Server End Points and Mode
	public $SERVERMODE;
	public $ENDPOINT;
	
	//Transaction
	public $TOKENRESPONSE;
	public $TXNTYPE;
	
	
	//Buyer Information
	public $NAME;
	public $CITY;
	public $STATE;
	public $COUNTRY;
	public $STREET;
	public $EMAIL;
	public $PHONE;
	public $ZIP;
	public $AMT;
	public $ORDERNUMBER;
	
	
	//Token
	public $SECURETOKENID;
	public $SECURETOKEN;
	
	
	/****************
	 'A'; // Authorization
	'S'; // SALE
	'C'; // Credit
	'V'; // VOID
	'D'; // Delayed Capture
	*/
	public function setTransactionType($txntype){
		$this->TXNTYPE=$txntype;
	}
	
	
	//****************** Server Mode ***********************************
	public function setServerMode($mode){
		$this->SERVERMODE=$mode;
		$this->ENDPOINT=$this->getServerUrl($mode);
	}
	
	//****************** Paypal Server Url ***********************************
	public function getServerUrl($mode){
		if($mode=="sand_box"){
			//Sanxbox
			return "https://pilot-payflowpro.paypal.com";
		}else{
			//Live
			return "https://payflowpro.paypal.com";
		}
	}
	
	
	//****************** Vendor Credentials ***********************************
	public function setVendorCredentials($user,$vendor,$partner,$pwd){
		$this->USER=$user;
		$this->VENDOR=$vendor;
		$this->PARTNER=$partner;
		$this->PWD=$pwd;
	}
	
	//****************** Amount ***********************************
	public function setAmount($amount){
		$this->AMT=$amount;
	}
	
	
	//****************** Order Invoice Number ***********************************
	public function setOrderInvoiceNumber($inv){
		$this->ORDERNUMBER=$inv;
	}
	
	

	
	
	//****************** Token Reponse Code***********************************
	//A value of 0 (zero) indicates that no errors occurred and the transaction was approved.
	//A value less than zero indicates that a communication error occurred. In this case, no transaction is attempted.
	//A value greater than zero indicates a decline or error (except in the case of RESULT 104.).
	//Readmore PDF Express Checkout for Payflow Pro (Page 45)
	
	public function getResponseCode($tokenResponse){
		//$tokenResponse=$this->TOKENRESPONSE;
		$responseCode='';
		foreach($tokenResponse as $key=>$value){
			$res = explode('=', $value);
			if($res[0]=="RESULT"){
				$responseCode=$res[1];
			}
		}
		return $responseCode;
	
	}
	
	//****************** Token Reponse Message***********************************
	public function getResponseMessage($tokenResponse){
		//$tokenResponse=$this->TOKENRESPONSE;
		//echo substr($tokenResponse[0],7);
		$responseMessage='';
		foreach($tokenResponse as $key=>$value){
			$res = explode('=', $value);
			if($res[0]="RESPMSG"){
				$responseMessage=$res[1];
			}
		}
		return $responseMessage;
	}
	
	
	//****************** Set Customer Information***********************************
	public function setCustomerInformation($NAME,$CITY,$STATE,$STREET,$EMAIL,$PHONE,$ZIP,$COUNTRY){
		$this->NAME=$NAME;
		$this->CITY=$CITY;
		$this->STATE=$STATE;
		$this->COUNTRY=$COUNTRY;
		$this->STREET=$STREET;
		$this->EMAIL=$EMAIL;
		$this->PHONE=$PHONE;
		$this->ZIP=$ZIP;
	}
	
	
	
	
	//getSecureToken() This function sets the values for the *secureTokenID, invoice number, and assigns other variables as needed for the call this uses hard coded values for example purposes. * @return array $response
	/*********************************************************************************************************************
	 TRXTYPE : How you want to obtain payment
	  	  - A indicates that this payment is an Authorization subject to settlement with the Delayed Capture request
	     - O indicates that this payment is an Order subject to settlement with the Delayed Capture request
	     - S indicates that this is a final Sale for which you are requesting payment
	       Note : NOTE:You cannot set this value to S in the Set Express Checkout request and then change this value to A on the final Do Express Checkout Payment request.
	    
	 TENDER : (Required) The tender type (method of payment). It is always P.
	 
	 ACTION : (Required) Is S to indicate this is a Set Express Checkout request.
	 
	 Amount (US Dollars) U.S. based currency. Must not exceed $10,000 USD in any currency. use 34.00, not 34.
	 
	 CURRENCY : (Required)  One of the supported currency codes USD , Us Dollar , AUD - Australian Dollar
	 
	 VERBOSITY : If you want to obtain the PayPal processor value, set the VERBOSITY parameter to MEDIUM. With this setting, the processor value is returned in the PROCAVS response parameter.
	 **********************************************************************************************************************/
	
	public function getSecureToken() { 
		//create a SECURETOKENID
		$secureTokenID = $this->guid (); // create a unique INVNUM
		$this->SECURETOKENID=$secureTokenID;
		$invnum = "INV" . $this->guid ();
		//$reqstr = "&TRXTYPE=A&" . "TENDER=C&" . "INVNUM=" . $invnum . "&AMT=". $this->AMT ."&"."CURRENCY=USD&" . "PONUM=&" . "STREET=&" . "NAME=&" . "CITY=&" . "STATE=&" . "ZIP=&" . "COUNTRY=US&" . "EMAIL=&" . "PHONE=&" . "CREATESECURETOKEN=Y&" . "VERBOSITY=HIGH&" . "SECURETOKENID=" . $secureTokenID;
	
		$reqstr = "&TRXTYPE=".$this->TXNTYPE . "&TENDER=C" . "&INVNUM=" . $this->ORDERNUMBER . "&AMT=". $this->AMT ."&CURRENCY=USD" . "&PONUM=" . "&STREET=". $this->STREET ."&NAME=" .$this->NAME. "&CITY=".$this->CITY . "&STATE=".$this->STATE . "&ZIP=".$this->ZIP . "&COUNTRY=US" . "&EMAIL=".$this->EMAIL . "&PHONE=" .$this->PHONE. "&CREATESECURETOKEN=Y&" . "VERBOSITY=HIGH&" . "SECURETOKENID=" . $secureTokenID;
// 		echo $reqstr;
// 		exit();
		$credstr = "USER=" . $this->USER . "&VENDOR=" . $this->VENDOR . "&PARTNER=" . $this->PARTNER . "&PWD=" . $this->PWD;
	
		//combine the strings
		$nvp_req = $credstr . $reqstr;
		
// 		drupal_json_output($nvp_req);
// 		exit();
		
		//set the endpoint to a local var:
		$endpoint = $this->ENDPOINT;
		
		//make the call
		$response = $this->PPHttpPost ( $endpoint, $nvp_req );
		return $response;
	}
	
	// end getToken call
	
	/*
	 * PPHttpPost(string, string) * PPHttpPost takes in two strings, and *makes a curl request and returns the result. @return array $httpResponseAr
	 */
	public function PPHttpPost($endpoint, $nvpstr) {
		// setting the curl parameters.
		$ch = curl_init ();
		curl_setopt ( $ch, CURLOPT_URL, $endpoint );
		curl_setopt ( $ch, CURLOPT_VERBOSE, 1 );
		// turning off the server and peer verification(TrustManager Concept).
		curl_setopt ( $ch, CURLOPT_SSL_VERIFYPEER, FALSE );
		curl_setopt ( $ch, CURLOPT_SSL_VERIFYHOST, FALSE );
		curl_setopt ( $ch, CURLOPT_RETURNTRANSFER, 1 );
		curl_setopt ( $ch, CURLOPT_POST, 1 );
		// setting the NVP $my_api_str as POST FIELD to curl
		curl_setopt ( $ch, CURLOPT_POSTFIELDS, $nvpstr );
		// getting response from server
		$httpResponse = curl_exec ( $ch );
		
		if (! $httpResponse) {
			$response = "API_method failed: " . curl_error ( $ch ) . '(' . curl_errno ( $ch ) . ')';
			return $response;
		}
		$httpResponseAr = explode ( "&", $httpResponse );
		return $httpResponseAr;
	} // end PPHttpPost function
	
	/*
	 * getMySecureToken(array) * This takes in the response array from the PPHttpPost call, and parses out the SecureToken * This is used because the securetoken may contain *an "=" sign * @return string $secure_token
	 */
	public function getMySecureToken($response) {
		$secure_token = $response [1];
		$secure_token = substr ( $secure_token, - 25 );
		return $secure_token;
	}
	// end getSecureToken()
	
	/*
	 * parseResponse(array) * This function parses out the response without taking into account that the securetoken may contain an "=" *sign. The only thing you need from this is the *SecureTokenID. * @return array $parsed_response
	 */
	public function parseResponse($response) {
		$parsed_response = array ();
		foreach ( $response as $i => $value ) {
			$tmpAr = explode ( "=", $value );
			if (sizeof ( $tmpAr ) > 1) {
				$parsed_response [$tmpAr [0]] = $tmpAr [1];
			}
		}
		return $parsed_response;
	} // end parseResponse
	
	/*
	 * getHTML(array, string) * This function dynamically builds the html code needed for the form post button. * @return string $html
	 */
	public function getHTML($response, $securetoken) {
		$html = "<div style='display:none;'><form name='pphs' id='pphs'  method='post' action='https://payflowlink.paypal.com/'> <input type='hidden' name='SECURETOKEN' value='$securetoken' /> <input type='hidden' name='SECURETOKENID' value='" . $response ['SECURETOKENID'] . "' /> <input type='hidden' name='MODE' value='test' /> <input type='submit' id='ck' /> </form></div>
				<script type='text/javascript'>document.pphs.submit();</script>";
		return $html;
	}
	
	

	// end getHTML
	
	/* guid() * *This function creates an MD5 hash of a timestamp *to be used with the SecureTokenID, and Invnum *in the initial call * *@return string $str */
	public function guid() { // hash out a timestamp and some chars to get a 25 char token to pass in
		$str = date ( 'l jS \of F Y h:i:s A' );
		$str = trim ( $str );
		$str = md5 ( $str );
		
		return $str;
	} // end guid
	
	
	
	public function log_payflow(){
		//date_default_timezone_set('Asia/Calcutta');
		$currDateTime = date('Y-m-d H:i:s', time());
		
		
		$nid = db_insert('paypal_payflow_log') 
		->fields(array(
				'orderid' => $this->ORDERNUMBER,
				'firstname' => $this->NAME,
				//'lastname' => $this->lastname,
				'phone' => $this->PHONE,
				'orderdate' => $currDateTime,
				'payment_status' => "Initiated",
				'amount' => $this->AMT,
				'securetoken' => $this->SECURETOKEN,
				'securetokenid' => $this->SECURETOKENID,
				
		))
		->execute();
		
	}
	
	public function update_payment_status(){
		//do updation
	}
	
	

}//end class
	
  


