
/*
 Copyright (C) 2014 Samuel D. Colak / AppShopBoys BV. All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of the author nor the names of its contributors may be used
 to endorse or promote products derived from this software without specific
 prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

@class Wizzpa;

/* 
 
 WIZZPA Architecture Information
 
 WIZZPA is a secure transit architecture that delivers messages to "endpoints" known as an "alias".

 Steps..
 
 1. First connect to WIZZPA's architecture
 2. Send ApplicationId and Secret to authenticate
 3. Send Alias Registration
 4. Send Messages (as many as you like) to an "alias"
 5. Disconnect
 
 If a message cannot be delivered immediately, it is stored on the Wizzpa Architecture until delivery
 succeeds OR the allocated expiry occurs.
 
 WIZZPA does NOT keep copies of messages after they are delivered so YOU are responsible for device message
 synchronization - HOWEVER if multiple devices ARE registered at the same time with the same alias, all devices
 WILL receive a copy of the message. Storage WILL NOT occur in this case.
 
*/

typedef void (^WizzpaCallbackBlock)(BOOL success, id result);


typedef NS_OPTIONS(NSUInteger, eWizzpaServiceStatus) {
	eWizzpaServiceStatusError = NSIntegerMax,
	eWizzpaServiceStatusDisconnected = 0,
	eWizzpaServiceStatusInitializing = 1,
	eWizzpaServiceStatusConnecting = 2,
	eWizzpaServiceStatusConnected = 3,
	eWizzpaServiceStatusAuthenticating = 4,
	eWizzpaServiceStatusAuthenticated = 5,
	eWizzpaServiceStatusDisconnecting = 6
};

typedef NS_OPTIONS(NSInteger, eSendState) {
	eSendStateFailed = 0,
	eSendStateSuccessAndRelayed = 1,
	eSendStateSuccessAndStored = 2
};

typedef NS_OPTIONS(NSInteger, eReasons) {
	eReasonDisconnectInvalidKey = 1,
	eReasonDisconnectApplicationIdInvalid = 2,
	eReasonDisconnectBanned = 3,
	eReasonRedirect = 10,
	eReasonDisconnectReasonsExpired = 99112,
	eReasonDisconnectReasonsTerminated = 99113,
	eReasonDisconnectReasonsAbuse = 99116,
	eReasonDisconnectReasonsBanned = 99117,
	eReasonDisconnectReasonsUnspecified = 99120,
};


@protocol WizzpaDelegate <NSObject>

@optional

	- (void) wizzpaWaitingForConnect:(Wizzpa*)service version:(int)version;

	- (void) wizzpaLogoutSuccessful:(Wizzpa*)service;

	- (void) wizzpaConnected:(Wizzpa*)service;

	- (void) wizzpaDisconnected:(Wizzpa*)service;

	- (void) wizzpa:(Wizzpa*)service serviceStatusChanged:(eWizzpaServiceStatus)status;

	- (void) wizzpa:(Wizzpa*)service messagesReceived:(NSArray*)messages;

	- (void) wizzpa:(Wizzpa*)service aliasBlocked:(NSString*)alias;

	- (void) wizzpa:(Wizzpa*)service serviceAnnouncement:(NSString*)message code:(int)code;

	- (void) wizzpa:(Wizzpa*)service blockListReceived:(NSArray*)blockList;

@end

@interface Wizzpa : NSObject

	@property (nonatomic, readonly, getter = getRegionId) int regionId;
	@property (nonatomic, readonly, getter = getServiceStatus) eWizzpaServiceStatus serviceStatus;

	+ (Wizzpa *) sharedInstance;
	+ (Wizzpa *) sharedInstance:(id<WizzpaDelegate>)delegateIn;

	- (void) connect:(NSString*)appId secret:(NSString*)secret block:(WizzpaCallbackBlock)block;

	- (void) logoutWithBlock:(WizzpaCallbackBlock)block;

	- (void) reconnect;

	- (void) disconnect;

	- (void) pollForMessages;

	- (void) registerAPNS:(NSString *)apns block:(WizzpaCallbackBlock)block;

	- (void) blockAlias:(NSString *)alias block:(WizzpaCallbackBlock)block;

	- (void) unblockAlias:(NSString *)alias block:(WizzpaCallbackBlock)block;

	- (void) notifyRecipient:(NSString *)alias message:(NSString*)message data:(NSString*)data badge:(NSUInteger)badge block:(WizzpaCallbackBlock)block;

	- (void) isAliasOnline:(NSString *)alias block:(WizzpaCallbackBlock)block;

	- (void) allAliasesOnlineWithBlock:(WizzpaCallbackBlock)block;

	- (void) registerAlias:(NSString*)alias block:(WizzpaCallbackBlock)block;

	- (void) send:(NSString*)alias domain:(NSString*)domain message:(NSString*)message block:(WizzpaCallbackBlock)block;

	- (void) sendToMany:(NSArray*)aliases domain:(NSString*)domain message:(NSString*)message block:(WizzpaCallbackBlock)block;


@end
