# AVX Framework

- a fork of https://github.com/kwonus/Digital-AV

It's been a quarter century since the first release of AV-Bible for Windows. In its day, it was the world's first <u>free</u> bible software with a graphical user interface that ran on Microsoft Windows. Originally conceived in 1992, this "Freeware" was maintained until 2011 and released as: AV-1995, AV-1996, AV-1997, ... , AV-2011. Eventually, it evolved into a software development kit (SDK). Accordingly, that SDK was renamed Digital-AV over a decade ago.

With respect to the Digital-AV, you can rely on its foundation. With countless deployments and extensive text validation, Digital-AV has travelled the world and back with feedback from Christian missionaries, pastors, and lay people. They used it in their ministries. In return, I received treasured quality-control feedback. By 2008, all of the textual bugs were ironed out. Not coincidentally, 2008 was the first release of the SDK. Never making a dime, and pouring a healthy chunk of my life into this effort: this has been a labor of love.

AVX-Framework represents a radical step forward at the same time as it reaches back to its roots as the fastest and most compact search tool for the KJV text. This fork from Digital-AV assembles all the pieces, conveniently in a single github repo.

The Digital-AV manifests the entire text of the bible, including Strong's numbers, Lemmatizations, Part-of-Speech tags, and other linguistic features into a single compactly formatted binary file. Notwithstanding, it is the KJV Bible at its core. Within this repo can be found the upgraded AVX-Omega-3911 data file that addresses a bug discovered in the previous Digital-AV Omega release. Bundling AVX assets into a dotnet-accessible framework not only streamlines development, but it also produces a fast and efficient search engine. It is fully optimized for searching the sacred text. Even fuzzy string matching is available, for the creation of rich, user-facing applications.

There is only one external dependency of AVX-Framework: that is FlatBuffers. It was selected for its speed, compactness, ubiquity, and its liberal license. It is used for communication with the Blueprint-Blue parser/library.

Of course, there are internal dependencies; these are open source projects, produced and maintained by AV Text Ministries, found at https://github.com/kwonus and https://github.com/AV-Text/AVX . 

The latest architecture is highly modularized. Earlier works were much more monolithic. While monolithic applications can be built faster, they are more fragile, difficult to refactor, and exhibit maintenance issues over the long haul. While a modular architecture is more labor-intensive year-by-year, it's way easier to refactor. Modularity facilitates incremental improvements that can be accomplished in shorter timeframes. In other words, it takes longer on the onset, but it's way better over time.

AV Text ministries hopes that you find assets here that can assist you in building next-gen, quality applications using the most trustworthy English text that God has yet availed to mankind [The Authorized Version 1769 text, commonly known as the King James Bible]. The Digital-AV license is designed to be as free as the gospel. Use it as you see fit, hopefully to the glory of God.

Consumers of AVX-Framework directly target a single dotnet assembly, namely AV-Engine. However, many publicly available classes are exposed in AVX-Lib-Net and NUPhone. It is expected that consumers of AV-Engine will reach into those two modules, but the other dependencies will be mostly opaque to AVX-Framework consumers. The seven modules that compose AVX-Framework are depicted in Figure-1:

![](AVXSearch/AVX-Framework.png)

**Figure-1**: AVX-Framework dependency diagram [revision #3A22]

A BETA release of AV-Bible and AV-Console are planned for 2023. The development roadmap for 2023 is depicted in Figure-2.

![](AVXSearch/AVX-Roadmap-2023.png)

**Figure-2**: Development roadmap for BETA releases in 2023 [revision #3A22]

We plan to harden AV-Bible (Windows desktop application) and release it into the Windows Store in the first quarter of 2024. Afterwards, additional apps will be implemented and released. The diagram, depicted in Figure-3, identifies anticipated application releases and estimated release dates:

![](AVXSearch/AVX-Roadmap-2024.png)

**Figure-3**: Roadmap for [user-facing] application releases in 2024 [revision #3A22]

The blue boxes, in the diagram, are being actively developed. Planned completion dates are identified. All source-code for these can be found in this [AVX] repo. The purple boxes are already complete. Work will commence on the gray boxes some time after the release of AV-Bible to the Windows Store.  It's helpful to have this pic as a roadmap. As you can see, AVX-Framework is a core dependency for all apps. For additional info on the purple boxes and the Digital-AV SDK, head on over to my other repos at  https://github.com/kwonus.

The AV-Bible application is currently available at the Windows Store as a free app. The existing app is being retrofitted to utilize the native C++ library implementations in the forthcoming AVX-Framework.  By incorporating the new framework into AV-Bible, there will be dozens of new features and capabilities.

**The Lord gave the word: great was the company of those that published it. -- Psalm 68:11**
