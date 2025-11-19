# Report
Fill out these report questions. 


1. What is the difference between a directed and undirected graph?

A directed graph has edges that only go one way. Basically it’s like a one way street, if there’s an edge from A to B, it doesn’t automatically mean you can go from B to A.

An undirected graph is the opposite. Every connection goes both ways. So if A is connected to B, then B is also connected to A without needing another edge. 

2. What is the Big O of Dijkstra's algorithm.... 
   * Assuming you used an array (or list) to store the vertices.
   * Assuming you used a heap / priority queue to store the vertices.

Using an array/list for the vertices (the version I used):
In my implementation, I used a normal array to keep track of distances and to find the next minimum vertex. Every time I pick the smallest unvisited node, I have to scan through the whole list. That makes the algorithm run in O(V²) time, where V is the number of vertices. It’s not the fastest possible, but it’s simple to write and easy to debug, which is why I went with it for this assignment.

Using a heap / priority queue:
If you replace the array with a min-heap or priority queue, finding the next closest vertex becomes much faster. The running time improves to O((V + E) log V), which is usually written as O(E log V) because edges dominate in big graphs. This version is better for large datasets, but it’s also more work to implement.

3. Explain in your own words what that means for larger graphs when trying to find the shortest distance. 

I stored all the city names in a CityList struct, which basically holds an array of strings and a count of how many cities there are. Each city ends up getting an index based on its position in that array. That index is what the rest of the program uses when building the graph or running Dijkstra. This way I don’t have to deal with strings when doing the actual graph calculations everything is just integer indices, which makes the graph logic way cleaner and faster.


## Deeper Thinking
4. For this assignment, you didn't need the most "efficient" set of data structures (for example, a heap wasn't required). However, think on the scale of google/apple maps - they have to deal with millions of vertices and edges. What data structures would you use to store the graph? Why? Somethings to consider - would you be able to store the entire graph at a time? Could you break it up into smaller pieces? How would you do that? Would there be advantages to caching/memoization of paths? You are free to explore your thoughts on this subject/reflect on various ideas. Other than a realization of some scalability of problems, there isn't a wrong answer. 

If I had to pick data structures for something that huge, I’d still use an adjacency list, mainly because it’s the most space-efficient way to store a big graph. An adjacency matrix would be way too large since most places aren’t directly connected.

For actually finding the shortest path, I’d probably use Dijkstra with a priority queue, just because I learned that it’s faster than scanning through an array each time like I did in my version. I’m definitely not an expert in map systems, but even that improvement would help a lot at a big scale.

I also don’t think you could keep the entire world map loaded at once. I’d imagine breaking it into chunks or sections, so you only load the part of the map you’re actually using.


## Future Understanding
5. Related to shortest distance, is a problem called the "messenger" or "traveling sales person" problem commonly abbreviated to TSP. This problem is to find the shortest path that visits **every** vertex in a graph. Another way to look at it, is you are an delivery driver, and you have a series of packages to deliver. Can you find an optimal path for your deliveries that minimizes the total distance traveled? Imagine if you had 5 stops. How many different paths are there?  There are 120 possible paths to look at! (assuming fully connected routes). 
   * How many possible paths are there if you have 6 stops?
   * How many possible paths are there if you have 10 stops?

This basically trying to find the shortest route that visits every stop exactly once. The number of possible routes blows up really fast because it’s based on factorials. If you have n stops, that’s n! different paths you could take. For example, with 5 stops you get 120 paths. If you go up to 6 stops, that jumps to 720 paths. And by the time you hit 10 stops, you’re looking at around 4 million different routes. So even adding just a couple more stops makes the number of possibilities get out of control really quickly. 

6. What type of growth is this problem? 
This problem grows factorially. That basically means every time you add one more stop, the number of possible paths multiplies by that number. So the growth gets out of hand really fast even faster than regular exponential growth. It's the kind of thing where a small increase in stops makes the problem way harder almost instantly.

7. Take some time to research TSP problems. It falls under a certain classification of problems? What is it? 

From what I found while reading about it, the Traveling Salesperson Problem is considered an NP-hard problem. I didn’t know what that meant at first, but basically it means there isn’t a simple or fast way to solve it for every case. The time it takes grows so quickly that computers struggle with it once the number of stops gets big. I came across a really straightforward explanation on the Brilliant.org TSP page, and they said TSP is one of the classic NP-hard problems because there’s no known fast algorithm that always finds the best route efficiently.
Reference: Brilliant.org — “Traveling Salesman Problem,” where they explain TSP being NP-hard in simple terms.

8. Provide some examples of fields / problems that use TSP.

I found that the Traveling Salesperson Problem actually shows up in a lot of real-world situations. The most obvious one is delivery routes, like UPS, or Amazon trying to figure out the best order to drop off packages. It also shows up in things like planning routes for salespeople or service workers who have multiple appointments in a day. Another example I saw was in manufacturing, where machines have to visit different points like drilling holes or cutting parts and want to do it in the shortest order. Basically, anytime something has to visit a bunch of locations and the goal is to reduce time or distance, it ends up being some version of TSP.



> [!TIP]
> We are having you explore TSP, so you can see the terms used for problem classification that are often the foundation of computer science theory. You will not be asked to know about TSP outside of this assignment or even problem classification. Computer Science is often about dealing with problems considered "too hard" or "impossible", and finding ways to make them possible! As such, knowing topics such as N, NP, NP-Complete, etc. is important to understand the limits (to break).


## Technical Interview Practice Questions
For both these questions, are you are free to use what you did as the last section on the team activities/answered as a group, or you can use a different question.

1. Select one technical interview question (this module or previous) from the [technical interview list](https://github.com/CS5008-khoury/Resources/blob/main/TechInterviewQuestions.md) below and answer it in a few sentences. You can use any resource you like to answer the question.

Question: What is a graph and its various components? What is a directed vs. undirected graph? Provide some real world uses for each.

Answer:  A graph is basically a structure that shows how different things are connected. It has two main parts: the vertices, which are the actual items like cities or people, and the edges, which are the connections between them like roads. Sometimes edges also have weights, which can represent things like distance or cost.

A directed graph is one where the connections only go one way, like a one way street. An undirected graph is the opposite the connection goes both ways. A real world example of a directed graph would be Instagram, where you can follow someone who doesn’t follow you back. An undirected graph is more like Facebook friendships, where both people are connected to each other.

2. Select one coding question (this module or previous) from the [coding practice repository](https://github.com/CS5008-khoury/Resources/blob/main/LeetCodePractice.md) and include a c file with that code with your submission. Make sure to add comments on what you learned, and if you compared your solution with others. 
