#ifndef CHUNK_H
#define CHUNK_H

#include <vox.h>

class Map;

class Chunk
{
	public:
	//	static float vertex[108];
	//	static	float uv[72];

		enum STATE
		{
			  INIT, 	//Just New
			  GENERATE, //World ready
			  THREAD,   //Thread Processing
			  BUILD,	//Vertex & UV ready to bind
			  RENDER,	//Bind & In render while
			  DISABLE,	//Out render and clean VAO from main thread
			  DELETE	//Ready to be delete
		};

		Chunk::STATE state;

		glm::vec3 worldCoord;
		glm::vec3 localCoord;

		unsigned int VAO;
		unsigned int VBO_VERT;
		unsigned int VBO_UV;

		size_t sizeuv;
		size_t sizevert;
		size_t nb;

		std::vector<glm::vec3> points;
		std::vector<glm::vec2> uvs;

		//noise::module::Perlin myModule;

		std::map<int,std::map<int,std::map<int,int> > > world;
		int minheight = 256;
		int maxheight = 0;

				Chunk(void);
				Chunk(int x, int y, int z);
				~Chunk(void);
		void	cleanVAO(void);

		void	generate(void);

		void 	build(void);
		void	buildFace(int n, int x, int y, int z, int val);

		bool	collide(int x, int y, int z, int way);
		int		getWorld(int x, int y, int z);


		float	*getVertices(void);
		size_t	getSizeVertices(void);
		float	*getUVs(void);
		size_t	getSizeUVs(void);

		size_t	getTriangle(void);


		unsigned int buildVAO();
};

#endif
