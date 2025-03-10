//
//  MobileAppTracker.h
//  MobileAppTracker
//
//  Created by HasOffers on 03/20/14.
//  Copyright (c) 2013 HasOffers. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "MATEvent.h"
#import "MATEventItem.h"
#import "MATPreloadData.h"

//#define MAT_USE_LOCATION
#ifdef MAT_USE_LOCATION
#import <CoreLocation/CoreLocation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#endif

#define MATVERSION @"3.9.1"


#pragma mark - enumerated types

/** @name Error codes */
typedef NS_ENUM(NSInteger, MATErrorCode)
{
    MATNoAdvertiserIDProvided       = 1101,
    MATNoConversionKeyProvided      = 1102,
    MATInvalidConversionKey         = 1103,
    MATServerErrorResponse          = 1111,
    MATInvalidEventClose            = 1131,
    MATTrackingWithoutInitializing  = 1132
};

/** @name Gender type constants */
typedef NS_ENUM(NSInteger, MATGender)
{
    MATGenderMale       = 0,                // Gender type MALE. Equals 0.
    MATGenderFemale     = 1,                // Gender type FEMALE. Equals 1.
    
    MAT_GENDER_MALE     = MATGenderMale,    // Backward-compatible alias for MATGenderMale.
    MAT_GENDER_FEMALE   = MATGenderFemale   // Backward-compatible alias for MATGenderFemale.
};


@protocol MobileAppTrackerDelegate;
#ifdef MAT_USE_LOCATION
@protocol MobileAppTrackerRegionDelegate;
#endif

/*!
 MobileAppTracker provides the methods to send events and actions to the
 HasOffers servers.
 */
@interface MobileAppTracker : NSObject


#pragma mark - Main Initializer

/** @name Intitializing MobileAppTracker With Advertiser Information */
/*!
 Starts Mobile App Tracker with MAT Advertiser ID and MAT Conversion Key. Both values are required.
 @param aid the MAT Advertiser ID provided in Mobile App Tracking.
 @param key the MAT Conversion Key provided in Mobile App Tracking.
 */
+ (void)initializeWithMATAdvertiserId:(NSString *)aid MATConversionKey:(NSString *)key;


#pragma mark - Delegate

/** @name MAT SDK Callback Delegate */
/*!
 [MobileAppTrackerDelegate](MobileAppTrackerDelegate) : A delegate used by the MobileAppTracker
 to post success and failure callbacks from the MAT servers.
 */
+ (void)setDelegate:(id <MobileAppTrackerDelegate>)delegate;

#ifdef MAT_USE_LOCATION
/** @name MAT SDK Region Delegate */
/*!
 [MobileAppTrackerRegionDelegate](MobileAppTrackerRegionDelegate) : A delegate used by the MobileAppTracker
 to post geofencing boundary notifications.
 */
+ (void)setRegionDelegate:(id <MobileAppTrackerRegionDelegate>)delegate;
#endif


#pragma mark - Debug And Test

/** @name Debug And Test */

/*!
 Specifies that the server responses should include debug information.
 @warning This is only for testing. You must turn this off for release builds.
 @param enable defaults to NO.
 */
+ (void)setDebugMode:(BOOL)enable;

/*!
 Set to YES to allow duplicate requests to be registered with the MAT server.
 
 @warning This is only for testing. You must turn this off for release builds.
 
 @param allow defaults to NO.
 */
+ (void)setAllowDuplicateRequests:(BOOL)allow;


#pragma mark - Behavior Flags
/** @name Behavior Flags */

/*!
 Check for a deferred deeplink entry point upon app installation.
 This is safe to call at every app launch, since the function does nothing
 unless this is the first launch.
 
 The timeout parameter should be set in keeping with the normal first-launch
 time and user experience of your app.
 
 @param timeout If the deeplink value is not received within this timeout duration, then the deeplink will not be opened.
 */
+ (void)checkForDeferredDeeplinkWithTimeout:(NSTimeInterval)timeout;

/*!
 Enable automatic measurement of app store in-app-purchase events. When enabled, your code should not explicitly measure events for successful purchases related to StoreKit to avoid event duplication.
 @param automate Automate IAP purchase event measurement. Defaults to NO.
 */
+ (void)automateIapEventMeasurement:(BOOL)automate;

/*!
 * Set whether the MAT events should also be logged to the Facebook SDK. This flag is ignored if the Facebook SDK is not present.
 * @param logging Whether to send MAT events to FB as well
 * @param limit Whether data such as that generated through FBAppEvents and sent to Facebook should be restricted from being used for other than analytics and conversions.  Defaults to NO.  This value is stored on the device and persists across app launches.
 */
+ (void)setFacebookEventLogging:(BOOL)logging limitEventAndDataUsage:(BOOL)limit;


#pragma mark - Data Setters

/** @name Setter Methods */

/*!
 Set whether this is an existing user or a new one. This is generally used to
 distinguish users who were using previous versions of the app, prior to
 integration of the MAT SDK. The default is to assume a new user.
 See http://support.mobileapptracking.com/entries/22621001-Handling-Installs-prior-to-SDK-implementation
 @param existingUser - Is this a pre-existing user of the app? Default: NO
 */
+ (void)setExistingUser:(BOOL)existingUser;

/*!
 Set the Apple Advertising Identifier available in iOS 6.
 @param appleAdvertisingIdentifier - Apple Advertising Identifier
 */
+ (void)setAppleAdvertisingIdentifier:(NSUUID *)appleAdvertisingIdentifier
           advertisingTrackingEnabled:(BOOL)adTrackingEnabled;

/*!
 Set the Apple Vendor Identifier available in iOS 6.
 @param appleVendorIdentifier - Apple Vendor Identifier
 */
+ (void)setAppleVendorIdentifier:(NSUUID * )appleVendorIdentifier;

/*!
 Sets the currency code.
 Default: USD
 @param currencyCode The string name for the currency code.
 */
+ (void)setCurrencyCode:(NSString *)currencyCode;

/*!
 Sets the jailbroken device flag.
 @param jailbroken The jailbroken device flag.
 */
+ (void)setJailbroken:(BOOL)jailbroken;

/*!
 Sets the package name (bundle identifier).
 Defaults to the Bundle Identifier of the app that is running the sdk.
 @param packageName The string name for the package.
 */
+ (void)setPackageName:(NSString *)packageName;

/*!
 Specifies if the sdk should auto detect if the iOS device is jailbroken.
 YES/NO
 @param autoDetect YES will detect if the device is jailbroken, defaults to YES.
 */
+ (void)setShouldAutoDetectJailbroken:(BOOL)autoDetect;

/*!
 Specifies if the sdk should pull the Apple Vendor Identifier from the device.
 YES/NO
 Note that setting to NO will clear any previously set value for the property.
 @param autoGenerate YES will set the Apple Vendor Identifier, defaults to YES.
 */
+ (void)setShouldAutoGenerateAppleVendorIdentifier:(BOOL)autoGenerate;

/*!
 Sets the site ID.
 @param siteId The MAT app/site ID of this mobile app.
 */
+ (void)setSiteId:(NSString *)siteId;

/*!
 Set the TRUSTe Trusted Preference Identifier (TPID).
 @param tpid - Trusted Preference Identifier
 */
+ (void)setTRUSTeId:(NSString *)tpid;

/*!
 Sets the MD5, SHA-1 and SHA-256 hash representations of the user's email address.
 @param userEmail The user's email address.
 */
+ (void)setUserEmail:(NSString *)userEmail;

/*!
 Sets the user ID.
 @param userId The string name for the user ID.
 */
+ (void)setUserId:(NSString *)userId;

/*!
 Sets the MD5, SHA-1 and SHA-256 hash representations of the user's name.
 @param userName The user's name.
 */
+ (void)setUserName:(NSString *)userName;

/*!
 Sets the MD5, SHA-1 and SHA-256 hash representations of the user's phone number.
 @param phoneNumber The user's phone number.
 */
+ (void)setPhoneNumber:(NSString *)phoneNumber;

/*!
 Set user's Facebook ID.
 @param facebookUserId string containing the user's Facebook user ID.
 */
+ (void)setFacebookUserId:(NSString *)facebookUserId;

/*!
 Set user's Twitter ID.
 @param twitterUserId string containing the user's Twitter user ID.
 */
+ (void)setTwitterUserId:(NSString *)twitterUserId;

/*!
 Set user's Google ID.
 @param googleUserId string containing the user's Google user ID.
 */
+ (void)setGoogleUserId:(NSString *)googleUserId;

/*!
 Sets the user's age.
 @param userAge user's age
 */
+ (void)setAge:(NSInteger)userAge;

/*!
 Sets the user's gender.
 @param userGender user's gender, possible values MATGenderMale, MATGenderFemale
 */
+ (void)setGender:(MATGender)userGender;

/*!
 Sets the user's location.
 @param latitude user's latitude
 @param longitude user's longitude
 */
+ (void)setLatitude:(double)latitude longitude:(double)longitude;

/*!
 Sets the user's location including altitude.
 @param latitude user's latitude
 @param longitude user's longitude
 @param altitude user's altitude
 */
+ (void)setLatitude:(double)latitude longitude:(double)longitude altitude:(double)altitude;

/*!
 Set app-level ad-tracking.
 YES/NO
 @param enable YES means opt-in, NO means opt-out.
 */
+ (void)setAppAdTracking:(BOOL)enable;

/*!
 Set whether the user is generating revenue for the app or not.
 If measureEvent is called with a non-zero revenue, this is automatically set to YES.
 @param isPayingUser YES if the user is revenue-generating, NO if not
 */
+ (void)setPayingUser:(BOOL)isPayingUser;

/*!
 Sets publisher information for attribution.
 @param preloadData Preload app attribution data
 */
+ (void)setPreloadData:(MATPreloadData *)preloadData;


#pragma mark - Data Getters

/** @name Getter Methods */

/*!
 Get the MAT ID for this installation (mat_id).
 @return MAT ID
 */
+ (NSString*)matId;

/*!
 Get the MAT log ID for the first app open (open_log_id).
 @return open log ID
 */
+ (NSString*)openLogId;

/*!
 Get whether the user is revenue-generating.
 @return YES if the user has produced revenue, NO if not
 */
+ (BOOL)isPayingUser;


#if USE_IAD

#pragma mark - Show iAd advertising

/** @name iAd advertising */

/*!
 Display an iAd banner in a parent view. The parent view will be faded in and out
 when an iAd is received or failed to display. The MobileAppTracker's delegate
 object will receive notifications when this happens.
 */
+ (void)displayiAdInView:(UIView *)view;

/*!
 Removes the currently displayed iAd, if any.
 */
+ (void)removeiAd;

#endif


#pragma mark - Measuring Sessions

/** @name Measuring Sessions */

/*!
 To be called when an app opens; typically in the applicationDidBecomeActive event.
 */
+ (void)measureSession;


#pragma mark - Measuring Events

/** @name Measuring Events */

/*!
 Record an event for an Event Name.
 @param eventName The event name.
 */
+ (void)measureEventName:(NSString *)eventName;

/*!
 Record an event by providing the equivalent Event ID defined on the MobileAppTracking dashboard.
 @param eventId The event ID.
 */
+ (void)measureEventId:(NSInteger)eventId;

/*!
 Record an event with a MATEvent.
 @param event The MATEvent.
 */
+ (void)measureEvent:(MATEvent *)event;


#pragma mark - Measuring Actions

/** @name Measuring Actions */

/*!
 Record an Action for an Event Name.
 @param eventName The event name.
 */
+ (void)measureAction:(NSString *)eventName DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEventName:(NSString *)eventName");

/*!
 Record an Action for an Event Name and reference ID.
 @param eventName The event name.
 @param refId The reference ID for an event, corresponds to advertiser_ref_id on the website.
 */
+ (void)measureAction:(NSString *)eventName referenceId:(NSString *)refId DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");


/*!
 Record an Action for an Event Name, revenue and currency.
 @param eventName The event name.
 @param revenueAmount The revenue amount for the event.
 @param currencyCode The currency code override for the event. Blank defaults to sdk setting.
 */
+ (void)measureAction:(NSString *)eventName
        revenueAmount:(float)revenueAmount
         currencyCode:(NSString *)currencyCode DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event Name and reference ID, revenue and currency.
 @param eventName The event name.
 @param refId The reference ID for an event, corresponds to advertiser_ref_id on the website.
 @param revenueAmount The revenue amount for the event.
 @param currencyCode The currency code override for the event. Blank defaults to sdk setting.
 */
+ (void)measureAction:(NSString *)eventName
          referenceId:(NSString *)refId
        revenueAmount:(float)revenueAmount
         currencyCode:(NSString *)currencyCode DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event ID.
 @param eventId The event ID.
 */
+ (void)measureActionWithEventId:(NSInteger)eventId DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEventId:(NSInteger)eventId");

/*!
 Record an Action for an Event ID and reference id.
 @param eventId The event ID.
 @param refId The reference ID for an event, corresponds to advertiser_ref_id on the website.
 */
+ (void)measureActionWithEventId:(NSInteger)eventId referenceId:(NSString *)refId DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event ID, revenue and currency.
 @param eventId The event ID.
 @param revenueAmount The revenue amount for the event.
 @param currencyCode The currency code override for the event. Blank defaults to sdk setting.
 */
+ (void)measureActionWithEventId:(NSInteger)eventId
                   revenueAmount:(float)revenueAmount
                    currencyCode:(NSString *)currencyCode DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event ID and reference id, revenue and currency.
 @param eventId The event ID.
 @param refId The reference ID for an event, corresponds to advertiser_ref_id on the website.
 @param revenueAmount The revenue amount for the event.
 @param currencyCode The currency code override for the event. Blank defaults to sdk setting.
 */
+ (void)measureActionWithEventId:(NSInteger)eventId
                     referenceId:(NSString *)refId
                   revenueAmount:(float)revenueAmount
                    currencyCode:(NSString *)currencyCode DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");


#pragma mark - Measuring Actions With Event Items (DEPRECATED)

/** @name Measuring Actions With Event Items */

/*!
 Record an Action for an Event Name and a list of event items.
 @param eventName The event name.
 @param eventItems An array of MATEventItem objects
 */
+ (void)measureAction:(NSString *)eventName eventItems:(NSArray *)eventItems DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event Name.
 @param eventName The event name.
 @param eventItems An array of MATEventItem objects
 @param refId The reference ID for an event, corresponds to advertiser_ref_id on the website.
 */
+ (void)measureAction:(NSString *)eventName
           eventItems:(NSArray *)eventItems
          referenceId:(NSString *)refId DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event Name.
 @param eventName The event name.
 @param eventItems An array of MATEventItem objects
 @param revenueAmount The revenue amount for the event.
 @param currencyCode The currency code override for the event. Blank defaults to sdk setting.
 */
+ (void)measureAction:(NSString *)eventName
           eventItems:(NSArray *)eventItems
        revenueAmount:(float)revenueAmount
         currencyCode:(NSString *)currencyCode DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event Name.
 @param eventName The event name.
 @param eventItems An array of MATEventItem objects
 @param refId The reference ID for an event, corresponds to advertiser_ref_id on the website.
 @param revenueAmount The revenue amount for the event.
 @param currencyCode The currency code override for the event. Blank defaults to sdk setting.
 */
+ (void)measureAction:(NSString *)eventName
           eventItems:(NSArray *)eventItems
          referenceId:(NSString *)refId
        revenueAmount:(float)revenueAmount
         currencyCode:(NSString *)currencyCode DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event Name.
 @param eventName The event name.
 @param eventItems An array of MATEventItem objects
 @param refId The reference ID for an event, corresponds to advertiser_ref_id on the website.
 @param revenueAmount The revenue amount for the event.
 @param currencyCode The currency code override for the event. Blank defaults to sdk setting.
 @param transactionState The in-app purchase transaction SKPaymentTransactionState as received from the iTunes store.
 */
+ (void)measureAction:(NSString *)eventName
           eventItems:(NSArray *)eventItems
          referenceId:(NSString *)refId
        revenueAmount:(float)revenueAmount
         currencyCode:(NSString *)currencyCode
     transactionState:(NSInteger)transactionState DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event Name.
 @param eventName The event name.
 @param eventItems An array of MATEventItem objects
 @param refId The reference ID for an event, corresponds to advertiser_ref_id on the website.
 @param revenueAmount The revenue amount for the event.
 @param currencyCode The currency code override for the event. Blank defaults to sdk setting.
 @param transactionState The in-app purchase transaction SKPaymentTransactionState as received from the iTunes store.
 @param receipt The in-app purchase transaction receipt as received from the iTunes store.
 */
+ (void)measureAction:(NSString *)eventName
           eventItems:(NSArray *)eventItems
          referenceId:(NSString *)refId
        revenueAmount:(float)revenueAmount
         currencyCode:(NSString *)currencyCode
     transactionState:(NSInteger)transactionState
              receipt:(NSData *)receipt DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event ID and a list of event items.
 @param eventId The event ID.
 @param eventItems An array of MATEventItem objects
 */
+ (void)measureActionWithEventId:(NSInteger)eventId eventItems:(NSArray *)eventItems DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event ID.
 @param eventId The event ID.
 @param eventItems An array of MATEventItem objects
 @param refId The reference ID for an event, corresponds to advertiser_ref_id on the website.
 */
+ (void)measureActionWithEventId:(NSInteger)eventId
                      eventItems:(NSArray *)eventItems
                     referenceId:(NSString *)refId DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event ID.
 @param eventId The event ID.
 @param eventItems An array of MATEventItem objects
 @param revenueAmount The revenue amount for the event.
 @param currencyCode The currency code override for the event. Blank defaults to sdk setting.
 */
+ (void)measureActionWithEventId:(NSInteger)eventId
                      eventItems:(NSArray *)eventItems
                   revenueAmount:(float)revenueAmount
                    currencyCode:(NSString *)currencyCode DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event ID.
 @param eventId The event ID.
 @param eventItems An array of MATEventItem objects
 @param refId The reference ID for an event, corresponds to advertiser_ref_id on the website.
 @param revenueAmount The revenue amount for the event.
 @param currencyCode The currency code override for the event. Blank defaults to sdk setting.
 */
+ (void)measureActionWithEventId:(NSInteger)eventId
                      eventItems:(NSArray *)eventItems
                     referenceId:(NSString *)refId
                   revenueAmount:(float)revenueAmount
                    currencyCode:(NSString *)currencyCode DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event ID.
 @param eventId The event ID.
 @param eventItems An array of MATEventItem objects
 @param refId The reference ID for an event, corresponds to advertiser_ref_id on the website.
 @param revenueAmount The revenue amount for the event.
 @param currencyCode The currency code override for the event. Blank defaults to sdk setting.
 @param transactionState The in-app purchase transaction SKPaymentTransactionState as received from the iTunes store.
 */
+ (void)measureActionWithEventId:(NSInteger)eventId
                      eventItems:(NSArray *)eventItems
                     referenceId:(NSString *)refId
                   revenueAmount:(float)revenueAmount
                    currencyCode:(NSString *)currencyCode
                transactionState:(NSInteger)transactionState DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");

/*!
 Record an Action for an Event ID.
 @param eventId The event ID.
 @param eventItems An array of MATEventItem objects
 @param refId The reference ID for an event, corresponds to advertiser_ref_id on the website.
 @param revenueAmount The revenue amount for the event.
 @param currencyCode The currency code override for the event. Blank defaults to sdk setting.
 @param transactionState The in-app purchase transaction SKPaymentTransactionState as received from the iTunes store.
 @param receipt The in-app purchase transaction receipt as received from the iTunes store.
 */
+ (void)measureActionWithEventId:(NSInteger)eventId
                      eventItems:(NSArray *)eventItems
                     referenceId:(NSString *)refId
                   revenueAmount:(float)revenueAmount
                    currencyCode:(NSString *)currencyCode
                transactionState:(NSInteger)transactionState
                         receipt:(NSData *)receipt DEPRECATED_MSG_ATTRIBUTE("Use +(void)measureEvent:(MATEvent *)event");


#pragma mark - Cookie Tracking

/** @name Cookie Tracking */
/*!
 Sets whether or not to use cookie based tracking.
 Default: NO
 @param enable YES/NO for cookie based tracking.
 */
+ (void)setUseCookieTracking:(BOOL)enable;


#pragma mark - App-to-app Tracking

/** @name App-To-App Tracking */

/*!
 Sets a url to be used with app-to-app tracking so that
 the sdk can open the download (redirect) url. This is
 used in conjunction with the setTracking:advertiserId:offerId:publisherId:redirect: method.
 @param redirectUrl The string name for the url.
 */
+ (void)setRedirectUrl:(NSString *)redirectUrl;

/*!
 Start an app-to-app tracking session on the MAT server.
 @param targetAppPackageName The bundle identifier of the target app.
 @param targetAppAdvertiserId The MAT advertiser ID of the target app.
 @param targetAdvertiserOfferId The MAT offer ID of the target app.
 @param targetAdvertiserPublisherId The MAT publisher ID of the target app.
 @param shouldRedirect Should redirect to the download url if the tracking session was 
   successfully created. See setRedirectUrl:.
 */
+ (void)startAppToAppTracking:(NSString *)targetAppPackageName
                 advertiserId:(NSString *)targetAppAdvertiserId
                      offerId:(NSString *)targetAdvertiserOfferId
                  publisherId:(NSString *)targetAdvertiserPublisherId
                     redirect:(BOOL)shouldRedirect;


#pragma mark - Re-Engagement Method

/** @name Application Re-Engagement */

/*!
 Record the URL and Source when an application is opened via a URL scheme.
 This typically occurs during OAUTH or when an app exits and is returned
 to via a URL. The data will be sent to the HasOffers server when the next
 measureXXX method is called so that a Re-Engagement can be recorded.
 @param urlString the url string used to open your app.
 @param sourceApplication the source used to open your app. For example, mobile safari.
 */
+ (void)applicationDidOpenURL:(NSString *)urlString sourceApplication:(NSString *)sourceApplication;


#ifdef MAT_USE_LOCATION
#pragma mark - Region Monitoring

/** @name Region monitoring */

/*!
 Begin monitoring for an iBeacon region. Boundary-crossing events will be recorded
 by the MAT servers for event attribution.
 
 When the first region is added, the user will immediately be prompted for use of
 their location, unless they have already granted it to the app.
 
 @param UUID The region's universal unique identifier (required).
 @param nameId The region's name, as programmed into the beacon (required).
 @param majorId A subregion's major identifier (optional, send 0)
 @param minorId A sub-subregion's minor identifier (optional, send 0)
 */

+ (void)startMonitoringForBeaconRegion:(NSUUID*)UUID
                                nameId:(NSString*)nameId
                               majorId:(NSUInteger)majorId
                               minorId:(NSUInteger)minorId;
#endif

@end


#pragma mark - MobileAppTrackerDelegate

/** @name MobileAppTrackerDelegate */

/*!
 Protocol that allows for callbacks from the MobileAppTracker methods.
 To use, set your class as the delegate for MAT and implement these methods.
 Delegate methods are called on an arbitrary thread.
 */
@protocol MobileAppTrackerDelegate <NSObject>
@optional

/*!
 Delegate method called when an action is enqueued.
 @param referenceId The reference ID of the enqueue action.
 */
- (void)mobileAppTrackerEnqueuedActionWithReferenceId:(NSString *)referenceId;

/*!
 Delegate method called when an action succeeds.
 @param data The success data returned by the MobileAppTracker.
 */
- (void)mobileAppTrackerDidSucceedWithData:(NSData *)data;

/*!
 Delegate method called when an action fails.
 @param error Error object returned by the MobileAppTracker.
 */
- (void)mobileAppTrackerDidFailWithError:(NSError *)error;

/*!
 Delegate method called when a deferred deeplink becomes available.
 @param deeplink String representation of the deeplink url.
 */
- (void)mobileAppTrackerDidReceiveDeeplink:(NSString *)deeplink;

/*!
 Delegate method called when an iAd is displayed and its parent view is faded in.
 */
- (void)mobileAppTrackerDidDisplayiAd;

/*!
 Delegate method called when an iAd failed to display and its parent view is faded out.
 */
- (void)mobileAppTrackerDidRemoveiAd;

/*!
 Delegate method called to pass through an iAd display error.
 @param error Error object returned by the iAd framework.
 */
- (void)mobileAppTrackerFailedToReceiveiAdWithError:(NSError *)error;

@end


#ifdef MAT_USE_LOCATION
#pragma mark - MobileAppTrackerRegionDelegate

/** @name MobileAppTrackerRegionDelegate */

/*!
 Protocol that allows for callbacks from the MobileAppTracker region-based
 methods. Delegate methods are called on an arbitrary thread.
 */

@protocol MobileAppTrackerRegionDelegate <NSObject>
@optional

/*!
 Delegate method called when an iBeacon region is entered.
 @param region The region that was entered.
 */
- (void)mobileAppTrackerDidEnterRegion:(CLRegion*)region;

/*!
 Delegate method called when an iBeacon region is exited.
 @param region The region that was exited.
 */
- (void)mobileAppTrackerDidExitRegion:(CLRegion*)region;

/*!
 Delegate method called when the user changes location authorization status.
 @param authStatus The new status.
 */
- (void)mobileAppTrackerChangedAuthStatusTo:(CLAuthorizationStatus)authStatus;

/*!
 Delegate method called when the device's Bluetooth settings change.
 @param bluetoothState The new state.
 */
- (void)mobileAppTrackerChangedBluetoothStateTo:(CBCentralManagerState)bluetoothState;

@end
#endif