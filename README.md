# Autonomous-Driving-Nanodegree


<div="content">
### Sobel Gradient
Canny edge Detection gives us a lot edges on scenery, cars, etc ended up discarding.
Using Sobel Gradient to detect vertical lines as lanes.
<ul>
  <li> Apply Sobel Operator, Sobel_x, Sobel_y in x,y directions
  <li> Apply a threshold to the overall magnitude of the gradient, in both x and y.
  <li> Apply a threshold to the overall direction of the gradient(arctan(sobel_y/sobel_x), [±π/2].
  <li> Combine thresholds for selection for pixels where both the xx and yy gradients meet the threshold criteria, or the gradient magnitude and direction are both within their threshold values.
</ul>
</div>
