WIZZPA COMMUNICATIONS SERVICE LAYER

This service allows developers to connect to the wizzpa communications infrastructure.


Some design concepts in play...

* alias is an endpoint - no user registration is required however aliases can be re-used - its the responsibility of the developer to maintain the integrity of the alias (ie that you are sure it is going someplace)

* wizzpa is based upon store and forward concepts. If the message cannot be delivered, it is stored until the alias appears online OR the timeout for the domain expires

* messages are arbitary units of bytes - wizzpa does not encrypt communications - only sends it forward.

* wizzpa servers are endpoints to a bigger infrastructure - simply put think of wizzpa endpoints as the edge-point of a cloud infrastructure

* messages are sent on "domains" - an example of a domain is "text" - each domain has a restrictive maximum trasmit size enforced by the service.

* when sending to a number of recipients, each recipient is sent a separate copy of the message. Consequently, if you send to 5 people you use 5*size of the message (if undelivered to all recipients).


Obtaining application ids and secrets

At the moment you need to contact us (wizzpa@appshopboys.com) for an id/secret - once you have this, you will have access to the infrastructure.

The infrastructure uses GEO-LOCATION over dns to give you the nearest endpoints into the infrastructure.

This is a paid service - consequently the following applies.

* Wizzpa charges based upon amount of data undelivered each day as of 12:00am GMT.

* The amount charged is dependant upon the thresholds exceeded per domain. Charges are per day. The first 50MB is free - over 50MB we implement charging.

	*  50MB - 100MB		10 euro / day
	* 100MB - 200MB		50 euro / day
	* 200MB - 500MB		200 euro / day
	
	
Service Availability

* The service functions on all iOS devices - (including the simulator) and MacOSX

* The service will be ported to Windows and Android devices shortly


Lastly

The infrastructure and code are all owned by AppShopBoys / Im-At-Home BV (code Copyright (C)2014/2015 Samuel Colak) - If you have any issues you can contact us at info@appshopboys.com.

