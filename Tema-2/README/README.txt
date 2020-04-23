--------------------------------- Input file format -----------------------------------------------

<count_students> <limit_students>
<name1> <program1>
<name2> <program2>
..................
<name[count_students]> <program[count_students]>
<count_sheets>
<name1> <count_programs1> 
		<program1> <count_courses1> 
			   <course_type1> <course_name1> (<option1> <option2>) <count_tests1>
					  <test_name1> <grade1>
					  <test_name2> <grade2>
					  .....................
					  <test_name[count_tests]> <grade[count_tests]>
			   <course_type2> <course_name2> (<option1> <option2>) <count_tests2>
					  .....................
					  .....................
		<program2> <count_courses2>
			   .................................................................
					  .....................
					  .....................
			   .................................................................
					  .....................
					  .....................
		
		
		............................................................................
		<program[count_programs]> <count_courses[count_programs]>
			   .................................................................
					  .....................
					  .....................
			   .................................................................
					  .....................
					  .....................

----------------------------------Training programs available-----------------------------------

Financier
{ 
	Mathematics ( Algebra ) 
	Finance
}

Manager
{
	Human_Resources 
	Finance
	Language ( English )
}

Programmer
{
	Mathematics ( Algebra Geometry Analysis )
	Programming ( OOP , C++ )
	Language ( English )
}

Developer_team_manager
{
	*Manager
	Programming ( OOP, C++)
	NLP_communication
}

Driver
{
	Driving_legislation
	Practical_car_driving ( Skoda )
}

Truckers_team_manager
{
	Language ( Turkish )
	*Manager
	Driving_legislation
}