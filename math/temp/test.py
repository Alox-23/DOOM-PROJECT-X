class Line:
    def __init__(self, point1, point2):
        self.point1 = point1
        self.point2 = point2
        self.calculate_equation()

    def calculate_equation(self):
        x1, y1 = self.point1
        x2, y2 = self.point2

        # Check if the line is vertical
        if x1 != x2:
            # Calculate the slope (m) and y-intercept (b)
            self.slope = (y2 - y1) / (x2 - x1)
            self.intercept = y1 - self.slope * x1
        else:
            # If the line is vertical, store slope as None and x-intercept
            self.slope = None
            self.intercept = x1

    def get_equation(self):
        if self.slope is not None:
            return f"y = {self.slope:.2f}x + {self.intercept:.2f}"
        else:
            return f"x = {self.intercept:.2f}"


# Example usage:
point1 = (2, 3)
point2 = (5, 9)
vertical_point1 = (4, 2)
vertical_point2 = (4, 8)

line = Line(point1, point2)
equation = line.get_equation()
print("Equation of the line:", equation)

vertical_line = Line(vertical_point1, vertical_point2)
vertical_equation = vertical_line.get_equation()
print("Equation of the vertical line:", vertical_equation)

