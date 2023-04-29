# AVX Search

- a fork of https://github/kwonus/Digital-AV

It's been over twenty-five years since the release of AV-Bible for Windows (also known as AV-1995). In its day, it was the first free bible software with a graphical user interface that ran on Microsoft Windows. This "Freeware" was maintained for more than a decade (AV-1996, AV-1997, ...). Eventually, it evolved into a software development kit (SDK). Accordingly, it was renamed Digital-AV some years ago.

You can rely on its foundation, with decades of deployments and text validation. Digital-AV has travelled the world and back with feedback from Christian missionaries. They used it in their ministries. In return, I received treasured quality-control feedback. By 2008, all of the textual bugs had been ironed out. Not coincidentally, 2008 was the first release of the SDK. Never making a dime, and pouring a healthy chuck of my life into it: this has been a labor of love.

AVX-Search represents a radical step forward at the same time as it reaches back to its roots as the fastest and most compact search tool for the KJV text. This fork from Digital-AV assembles all the pieces into a whole.

The Digital-AV SDK is a single 19mb file that can be used to manifest the entire text of the bible, including Strong's numbers, Lemmatizations, Part-of-Speech tags, and other linguistic features. But even with all of that, it's still the KJV Bible at the core. AVX-Search utilizes the C++ foundations of that SDK. That coupled with some open source parsing engines composes a fast and efficient search engine with a minimal set of dependencies.

One dependency that is rolled in here is FlatBuffers, due to its speed, compactness, and ubiquity.

The other dependencies are open source projects, produced and managed by AV Text Ministries. [http://github/kwonus]

How they relate to AVX-Search is depicted in this diagram:

![](AVXSearch/AVXSearch-context.png)

The Blue boxes above are all in active deployment. As such end-user apps are not yet available. They are expected to be completed in 2023. After that, status will be evaluated and work can commence on the gray boxes.  Still it's helpful to have this pic as a roadmap. Some architectural decisions actually mitigate this recent surprise. A dotnet app is unable to perform interop with x64 C++ via P/Invoke. The architecture above accordingly has much less dotnet in it than previous picture. As you can see, AVX-Search is a central dependency in the overall user-facing apps. As such dotnet components are a much less significant aspect of downstream development. For additional details on any of the blue boxes, head on over to  http://github/kwonus, and browse the repositories there.

The Lord gave the word: great was the company of those that published it. -- Psalm 68:11
