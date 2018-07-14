/**
 * @file
 * $Revision: 1.5 $
 * $Date: 2008/05/09 18:49:25 $
 *
 *   Unless noted otherwise, the portions of Isis written by the USGS are public
 *   domain. See individual third-party library and package descriptions for
 *   intellectual property information,user agreements, and related information.
 *
 *   Although Isis has been used by the USGS, no warranty, expressed or implied,
 *   is made by the USGS as to the accuracy and functioning of such software
 *   and related material nor shall the fact of distribution constitute any such
 *   warranty, and no responsibility is assumed by the USGS in connection
 *   therewith.
 *
 *   For additional information, launch
 *   $ISISROOT/doc//documents/Disclaimers/Disclaimers.html in a browser or see
 *   the Privacy &amp; Disclaimers page on the Isis website,
 *   http://isis.astrogeology.usgs.gov, and the USGS privacy and disclaimers on
 *   http://www.usgs.gov/privacy.html.
 */

#include "DetectedContour.h"

namespace Isis {

  /**
   * Default constructor. The contour's location will be initialized to 0,0
   * and its height and length will be initialized to 0.
   */
  DetectedContour::DetectedContour() {
    m_massCenter = Point2f(0,0);
    m_boundingRectangle = Rect(0,0,0,0);
    m_lineOffset = 0;
    m_valid = true;
  }


  /**
   * Construct a DetectedContour from a mass center and bounding rectangle.
   * 
   * @param massCenter The center of the contour.
   * @param boundingRectangle The smallest rectangle that completely encloses the contour.
   */
  DetectedContour::DetectedContour(Point2f massCenter, Rect boundingRectangle) {
    m_massCenter = massCenter;
    m_boundingRectangle = boundingRectangle;
    m_lineOffset = 0;
    m_valid = true;
  }


  /**
   * Destroy a DetectedContour.
   */
  DetectedContour::~DetectedContour() {
  }


  /**
   * Operator for comparing two contours.  This is for sorting marks before numbering.
   * 
   * @param other The contour to compare this with.
   * 
   * @return @b bool If this is less than the other contour.
   */
  bool DetectedContour::operator<(const DetectedContour &other) const{
    bool results;
    if (fabs(sample() - other.sample()) > 80) {
      results = sample() < other.sample();
    }
    else {
      results = line() < other.line();
    }
    return results;
  }


  /**
   * Return the center point of the contour.
   * 
   * @return @b Point2f The center of the contour as an OpenCV point.
   */
  Point2f DetectedContour::massCenter() const{
    return m_massCenter;
  }


  /**
   * Return the bounding rectangle of the contour.
   * 
   * @return @b Rect The bounding rectangle of the contour as an OpenCV rectangle.
   */
  Rect DetectedContour::boundingRect() const{
    return m_boundingRectangle;
  }


  /**
   * Return the center sample of the contour.
   * 
   * @return @b double The sample of the mass center of the contour.
   */
  double DetectedContour::sample() const{
    return m_massCenter.x;
  }


  /**
   * Return the center line of the contour.
   * 
   * @return @b double The line of the mass center of the contour.
   */
  double DetectedContour::line() const{
    return m_massCenter.y + m_lineOffset;
  }


  /**
   * Return the leftmost sample of the contour.
   * 
   * @return @b int The left sample of the contour.
   */
  int DetectedContour::leftSample() const{
    return m_boundingRectangle.x;
  }


  /**
   * Return the rightmost sample of the contour.
   * 
   * @return @b int The rightmost sample of the contour.
   */
  int DetectedContour::rightSample() const{
    return m_boundingRectangle.x + m_boundingRectangle.width;
  }


  /**
   * Return the top line of the contour.
   * 
   * @return @b int The top line of the contour.
   */
  int DetectedContour::topLine() const{
    return m_boundingRectangle.y + m_lineOffset;
  }


  /**
   * Return the bottom line of the contour.
   * 
   * @return @b int The bottom line of the contour.
   */
  int DetectedContour::bottomLine() const{
    return m_boundingRectangle.y + m_boundingRectangle.height + m_lineOffset;
  }


  /**
   * Return the length of the contour.
   * 
   * @return @b int The length of the contour's bounding rectangle.
   */
  int DetectedContour::length() const{
    return m_boundingRectangle.width;
  }


  /**
   * Return the height of the contour.
   * 
   * @return @b int The height of the contour's bounding rectangle.
   */
  int DetectedContour::height() const{
    return m_boundingRectangle.height;
  }


  /**
   * If the contour is valid.
   * 
   * @return @b bool If the contour is valid.
   */
  bool DetectedContour::valid() const{
    return m_valid;
  }


  /**
   * Set the validity of the contour.
   * 
   * @param validity If the contour is valid.
   */
  void DetectedContour::setValid(bool validity) {
    m_valid = validity;
  }


  /**
   * Set the line offset of the contour.
   * 
   * @param offset The new line offset.
   */
  void DetectedContour::setLineOffset(int offset) {
    m_lineOffset = offset;
  }


/*************************************************************************************************
 * TimingMark class
 *************************************************************************************************/


  /**
   * Default constructor
   */
  TimingMark::TimingMark() {
    m_lineOffset = 24900;
    m_number = -1;
    m_value = -1;
    m_time = -1;
    m_exposureTime = -1;
  }


  /**
   * Construct a TimingMark from a mass center and bounding rectangle.  The timing mark's number,
   * value, time, and exposure time are set to -1.
   * 
   * @param massCenter The center of the TimingMark.
   * @param boundingRectangle The smallest rectangle that completely encloses the TimingMark.
   */
  TimingMark::TimingMark(Point2f massCenter, Rect boundingRectangle):
              DetectedContour(massCenter, boundingRectangle) {
    // Initialize unknown members to -1
    m_lineOffset = 24900;
    m_number = -1;
    m_value = -1;
    m_time = -1;
    m_exposureTime = -1;
  }


  /**
   * Construct a TimingMark from a DetectedContour.
   * 
   * @param contour The contour to construct from.
   */
  TimingMark::TimingMark(DetectedContour contour):
              DetectedContour(contour.massCenter(), contour.boundingRect()) {
    setValid(contour.valid());
    m_lineOffset = 24900;
    m_number = -1;
    m_value = -1;
    m_time = -1;
    m_exposureTime = -1;
  }


  /**
   * Return the TimingMark's number.
   * 
   * @return @b int The TimingMark's number, ordered from left to right on the image.
   */
  int TimingMark::number() const{
    return m_number;
  }


  /**
   * Return the TimingMark's value.
   * 
   * @return @b int The TimingMark's value in the time code.
   */
  int TimingMark::value() const{
    return m_value;
  }


  /**
   * Return the start time of the TimingMark.
   * 
   * @return @b double The time the TimingMark starts in J2000.
   */
  double TimingMark::time() const{
    return m_time;
  }


  /**
   * Return the exposure time for a sample between the start of this TimingMark and
   * the next start of the next TimingMark.
   * 
   * @return @b double The seconds per sample exposure time for this TimingMark.
   */
  double TimingMark::exposureTime() const{
    return m_exposureTime;
  }


  /**
   * Set the TimingMark's number.
   * 
   * @param number The TimingMark's number.
   */
  void TimingMark::setNumber(int number) {
    m_number = number;
  }


  /**
   * Set the TimingMark's value.
   * 
   * @param value The TimingMark's value.
   */
  void TimingMark::setValue(int value) {
    m_value = value;
  }


  /**
   * Set the start time for the TimingMark.
   * 
   * @param time The start time for the TimingMark in J2000.
   */
  void TimingMark::setTime(double time) {
    m_time = time;
  }


  /**
   * Set the exposure time for the TimingMark.
   * 
   * @param exposureTime The exposure time for the TimingMark in seconds per sample.
   */
  void TimingMark::setExposureTime(double exposureTime) {
    m_exposureTime = exposureTime;
  }


  /**
   * Adjusts the timing mark's location.
   * 
   * @param startSample The new sample at which the mark starts
   * @param stopSample The new sample at which the mark stops
   * @param line The new center line
   */
  void TimingMark::adjustLocation(int startSample, int stopSample, int line) {
    Rect adjustedRectanlge(stopSample, line - m_boundingRectangle.height/2,
                           startSample - stopSample, m_boundingRectangle.height);
    Point2f adjustedCenter((float)(startSample + stopSample)/2, (float)line);
    m_boundingRectangle = adjustedRectanlge;
    m_massCenter = adjustedCenter;
  }


/*************************************************************************************************
 * FiducialMark Class
 *************************************************************************************************/


  /**
   * Default constructor
   */
  FiducialMark::FiducialMark() {
    m_lineOffset = 0;
    m_number = -1;
    m_calibratedX = 0;
    m_calibratedY = 0;
    m_residualX = 0;
    m_residualY = 0;
    m_residualMagnitude = 0;
  }


  /**
   * Construct a FiducialMark from a mass center and a bounding rectangle.
   * The FiducialMark's number is set to -1.  The FiducialMark's expected image location
   * is set to 0,0 and its residual vector is set to 0.
   * 
   * @param massCenter The center of the FiducialMark.
   * @param boundingRectangle The smallest rectangle that completely encloses the FiducialMark.
   */
  FiducialMark::FiducialMark(Point2f massCenter, Rect boundingRectangle):
                DetectedContour(massCenter, boundingRectangle) {
    //Initialize the number to -1
    if (massCenter.y < 200) {
      m_lineOffset = 1000;
    }
    else {
      m_lineOffset = 24300;
    }
    m_number = -1;
    m_calibratedX = 0;
    m_calibratedY = 0;
    m_residualX = 0;
    m_residualY = 0;
    m_residualMagnitude = 0;
  }


  /**
   * Construct a FiducialMark from a DetectedContour.
   * 
   * @param contour The DetectedContour to construct from.
   */
  FiducialMark::FiducialMark(DetectedContour contour):
                DetectedContour(contour.massCenter(), contour.boundingRect()) {
    setValid(contour.valid());
    if (contour.massCenter().y < 200) {
      m_lineOffset = 1000;
    }
    else {
      m_lineOffset = 24300;
    }
    m_number = -1;
    m_calibratedX = 0;
    m_calibratedY = 0;
    m_residualX = 0;
    m_residualY = 0;
    m_residualMagnitude = 0;
  }


  /**
   * Operator defining how to compare fiducial marks for sorting.
   * This determines how the fiducial marks are numbered.
   */
  bool FiducialMark::operator<(const FiducialMark &other) const{
    bool results;
    if (fabs(sample() - other.sample()) > 200) {
      results = sample() < other.sample();
    }
    else {
      results = line() < other.line();
    }
    return results;
  }


  /**
   * Return the FiducialMark's number.
   * 
   * @return @b int The FiducialMark's number.
   */
  int FiducialMark::number() const{
    return m_number;
  }


  /**
   * Return the calibrated X coordinate for this FiducialMark.
   * 
   * @return @b double The calibrated X coordinate.
   */
  double FiducialMark::calibratedX() const {
    return m_calibratedX;
  }


  /**
   * Return the calibrated Y coordinate for this FiducialMark.
   * 
   * @return @b double The calibrated Y coordinate.
   */
  double FiducialMark::calibratedY() const {
    return m_calibratedY;
  }


  /**
   * Return the X residual for the FiducialMark.
   * 
   * @return @b double The mark's X residual.
   */
  double FiducialMark::residualX() const {
    return m_residualX;
  }


  /**
   * Return the Y residual for the FiducialMark.
   * 
   * @return @b double The mark's Y residual.
   */
  double FiducialMark::residualY() const {
    return m_residualY;
  }


  /**
   * Return the magnitude of the residual for the FiducialMark
   * 
   * @return @b double The magnitude of the mark's residual.
   */
  double FiducialMark::residualMagnitude() const {
    return m_residualMagnitude;
  }


  /**
   * Set the FiducialMark's number.
   * 
   * @param number The FiducialMark's number.
   */
  void FiducialMark::setNumber(int number) {
    m_number = number;
  }


  /**
   * Set the FiducialMark's calibrated X coordinate.
   * 
   * @param calValue The calibrated X coordinate.
   */
  void FiducialMark::setCalibratedX(double calValue) {
    m_calibratedX = calValue;
  }


  /**
   * Set the FiducialMark's calibrated Y coordinate.
   * 
   * @param calValue The calibrated Y coordinate.
   */
  void FiducialMark::setCalibratedY(double calValue) {
    m_calibratedY = calValue;
  }


  /**
   * Set the FiducialMark's X residual.
   * 
   * @param residual The X residual.
   */
  void FiducialMark::setResidualX(double residual) {
    m_residualX = residual;
  }


  /**
   * Set the FiducialMark's Y residual/
   * 
   * @param residual The Y residual.
   */
  void FiducialMark::setResidualY(double residual) {
    m_residualY = residual;
  }


  /**
   * Compute the magnitude of the FiducialMark's residual vector
   * based on the stored X and Y residuals.
   */
  void FiducialMark::computeResidualMagnitude() {
    m_residualMagnitude = sqrt(m_residualX * m_residualX + m_residualY * m_residualY);
  }


  /**
   * Adjust the fiducial mark's location.
   * 
   * @param sample The new center sample
   * @param line The new center line
   */
  void FiducialMark::adjustLocation(double sample, double line) {
    Rect adjustedRectanlge((int)sample - m_boundingRectangle.width/2,
                           (int)line - m_boundingRectangle.height,
                           m_boundingRectangle.width, m_boundingRectangle.height);
    if (line < 200) {
      m_lineOffset = 1000;
    }
    else {
      m_lineOffset = 24300;
    }
    Point2f adjustedCenter((float)sample, (float)line);
    m_boundingRectangle = adjustedRectanlge;
    m_massCenter = adjustedCenter;
    
  }
};