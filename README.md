# Novomatic-Internship
This project includes three tasks, all implemented using Visual Studio 2019. 

## Task 1:
Used libraries:

[GLAD](https://glad.dav1d.de)

[GLFW](https://www.glfw.org)


I implemented triangle collision detection by checking whether any combination of the edges of two triangles intersects. If there is an intersection, then there is a collision and the background color is changed to red. The implementation assumes that triangles can share a vertex, an edge, or overlap each other.

You can move one triangle with arrow keys. 
![Screenshot_3](https://user-images.githubusercontent.com/115038725/236938828-49aa1d0e-1b67-40a3-a1a5-d4147ff631fe.jpg)
![Screenshot_2](https://user-images.githubusercontent.com/115038725/236938852-8bfbbb09-7a14-46cd-91af-e5cdb3b35ffc.jpg)
![Screenshot_4](https://user-images.githubusercontent.com/115038725/236938859-e290d021-405c-430f-b656-03cf9fcec4e1.jpg)
![Screenshot_5](https://user-images.githubusercontent.com/115038725/236938868-addd1d61-9710-431c-bda2-c4963bafc1ef.jpg)

## Task 2:

In this task, I implemented pixel shifting in the correct order five times. During the execution, the position of the pixel and the current duration are continuously printed.
![Screenshot_6](https://user-images.githubusercontent.com/115038725/236939218-d4d00689-0bca-48cb-a793-0be22377c49e.jpg)


## Task 3:

I used [Catch2](https://github.com/catchorg/Catch2) for testing. 

In my version of string trimming from the left and right, we have the ability to provide 2 predicates, which allows trimming from both sides based on different predicates. We can provide any user-defined predicate.\

![image](https://user-images.githubusercontent.com/115038725/236940086-e02aa352-9aaa-47ba-a82b-76783e7bcd69.png)
