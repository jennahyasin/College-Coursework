package com.example.csumb_csit_course;
/*
 *CST 338: Software Design - Android App
 * This program creates an Android application that uses ListView to implement
 * the list of the required courses in order to complete the CS online degree
 * and displays each course's description.
 */
//All needed imports
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import android.content.Intent;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

public class MainActivity extends AppCompatActivity
{
    ListView courses;
    Button event;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        courses = findViewById(R.id.list);
        final TextView displayDescription = (TextView) findViewById(R.id.courseDescription);
        //Creates a string for all of the course names
        String[] courseNames = new String[]{
                "CST 300: Major ProSeminar",
                "CST 338: Software Design",
                "CST 363: Database Management",
                "CST 334: Operating Systems",
                "CST 311: Introduction to Computer Networking",
                "CST 336: Internet Programming",
                "CST 462S: Race, Gender, Class in the Digital World",
                "CST 328: Digital Art and Design",
                "CST 370: Algorithms",
                "CST 383: Introduction to Data Science",
                "CST 438: Software Engineering",
                "CST 329: Reasoning with Logic",
                "CST 489: Capstone Project Planning",
                "CST 499: Directed Group Capstone"
                };
        List<String> courseList = new ArrayList<String>(Arrays.asList(courseNames));

        ArrayAdapter<String> array = new ArrayAdapter<String>
                (this, R.layout.support_simple_spinner_dropdown_item, courseNames);
        courses.setAdapter(array);
        //Checks which course is being clicked by checking the string and displaying the corresponding
        //course description.
        courses.setOnItemClickListener(new AdapterView.OnItemClickListener()
        {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id)
            {
                String courseClicked = (String) parent.getItemAtPosition(position);

                if(courseClicked == "CST 300: Major ProSeminar")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nHelps students identify and articulate personal, professional, and social goals. " +
                            "Provides an integrated overview of the computer science and communication design majors and their requirements. " +
                            "Students develop a plan for their learning goals. Students learn writing, presentation, research and critical-thinking " +
                            "skills within the diversified fields of information technology and communication design. Students " +
                            "learn how to analyze, predict, and articulate trends in the academic, public service.");
                }
                else if(courseClicked == "CST 338: Software Design")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nProvides students with the fundamental concepts to develop large-scale software," +
                            " focusing on the object-oriented programming techniques. Coverage includes the introduction " +
                            "to Java programming language, object-oriented programming, software life cycle and " +
                            "development processes, requirements analysis, and graphical user interface development.");
                }

                else if(courseClicked == "CST 363: Database Management")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nThis course provides balanced coverage of " +
                            "database use and design,focusing on relational databases. Students will learn to design " +
                            "relational schemas, write SQL queries, access a DB programmatically,and perform database " +
                            "administration. Students will gain a working knowledge of the algorithms and data " +
                            "structures used in query evaluation and transaction processing. Students will also " +
                            "learn to apply newer database technologies such as XML, NoSQL, and Hadoop.");
                }

                else if(courseClicked == "CST 334: Operating Systems")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nStudents in this course will learn " +
                            "about the use and design of modern operating systems, focusing on Linux. On " +
                            "the “use” side, students will learn the Linux command line, to write shell " +
                            "scripts, and to build programs with GNU utilities like awk, sed, and make. " +
                            "On the “design” side, students will develop a deep understanding of process " +
                            "management, memory management, file systems, and concurrency, and how they apply " +
                            "to modern technologies like virtualization and cloud computing.");
                }

                else if(courseClicked == "CST 311: Introduction to Computer Networking")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nSurvey of Telecomm and Data Comm Technology " +
                            "Fundamentals, Local Area Network, Wide Area Network, Internet and internetworking protocols including" +
                            " TCP/IP, network security and performance, emerging industry trends such as voice over the network and " +
                            "high speed networking. Designed as a foundation for students who wish to pursue more advanced network " +
                            "studies including certificate programs. Includes hands-on networking labs that " +
                            "incorporate Cisco CCNA lab components.");
                }

                else if(courseClicked == "CST 336: Internet Programming")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nProvides students with dynamic web application " +
                            "development skills, focusing on the integration of server-side programming, database connectivity," +
                            " and client-side scripting. Coverage includes the Internet architecture, responsive design, " +
                            "RESTful web services, and Web APIs.");
                }

                else if(courseClicked == "CST 462S: Race, Gender, Class in the Digital World")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nProvides students with key knowledge of " +
                            "race, gender, class and social justice especially in relation to technology in " +
                            "today’s digital world. Students challenge the barriers of expertise, gender, race, " +
                            "class, and location that restrict wider access to and understanding of the production and " +
                            "usage of new technologies.");
                }

                else if(courseClicked == "CST 328: Digital Art and Design")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nA survey course that combines the study of" +
                            " technology, design and aesthetic principles as they apply to twenty-first century visual media. " +
                            "Students learn how fundamental concepts of art and design apply to a broad range of commercial, " +
                            "expressive and entertainment forms. Students also study the democratization of the creative process " +
                            "through digital media, using current technology to produce sophisticated and expressive examples " +
                            "of personal digital creativity.");
                }

                else if(courseClicked == "CST 370: Algorithms")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nStudents learn important data structures in " +
                            "computer science and acquire fundamental algorithm design techniques to get the efficient solutions to " +
                            "several computing problems from various disciplines. Topics include the analysis of algorithm efficiency, " +
                            "hash, heap, graph, tree, sorting and searching, brute force, divide-and-conquer, decrease-and-conquer, " +
                            "transform-and-conquer, dynamic programming, and greedy programming.");
                }

                else if(courseClicked == "CST 383: Introduction to Data Science")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nIn data science, data analysis and machine learning " +
                            "techniques are applied to visualize data, understand trends, and make predictions. In this course students will " +
                            "learn how to obtain data, preprocess it, apply machine learning methods, and visualize the results. A student" +
                            " who completes the course will have enough theoretical knowledge, and enough skill with modern statistical " +
                            "programming languages and their libraries,to define and perform complete data science projects.");
                }

                else if(courseClicked == "CST 438: Software Engineering")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nPrepares students for large-scale software development " +
                            "using software engineering principles and techniques. Coverage includes software process, requirements analysis" +
                            " and specification, software design, implementation, testing, and project management. Students are expected to work" +
                            " in teams to carry out a realistic software project.");
                }

                else if(courseClicked == "CST 329: Reasoning with Logic")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nIn this course students learn to develop skill in using " +
                            "logic to describe and assess arguments. Students will learn to write formulas in propositional and first-order" +
                            " logic, and more importantly, to write and check proofs. Students will also learn to write formulas" +
                            " in three-valued and modal logic, know how to choose an appropriate logic, and understand the " +
                            "limitations of logic in capturing human reasoning.");
                }

                else if(courseClicked == "CST 489: Capstone Project Planning")
                {
                    displayDescription.setText("Course Clicked: " + courseClicked + "\nA class that focuses on the prepartion of "+
                            "the capstone project that will be due by the end of the last course of the program.");
                }
                else{
                    displayDescription.setText("Course Clicked: " + courseClicked + "\n Students will work on a project in large " +
                            "groups (up to 5 students in each group), developing requirements specification, a solution plan followed by " +
                            "design and implementation of the solution. The problem statement for the projects will be " +
                            "selected by the faculty. Faculty will also play the role of a project manager directing the " +
                            "schedule and deliverables for these projects.");
                }
            }
        });
        //Connects the two activity pages together by using Intent function. When button is clicked,
        //opens the video which is in the Video class.
        event = findViewById(R.id.videoButton);
        event.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                Toast.makeText(getApplicationContext(), "Button Clicked", Toast.LENGTH_SHORT).show();

                Intent intent = new Intent(getApplicationContext(), Video.class);
                startActivity(intent);
            }
        });
    }
}