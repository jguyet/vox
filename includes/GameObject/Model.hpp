#ifndef MODEL_H
#define MODEL_H

# include <vox.h>
# include <assimp/Importer.hpp>
# include <assimp/scene.h>
# include <assimp/postprocess.h>
# include <GameObject/Mesh.hpp>
# include <GameObject/Component.hpp>

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
struct Texture;
class Mesh;
class Camera;

class Model : public Component
{
	public:
		static std::map<const std::string, Model*>	model;

		Shader 			*shader;

	    /*  Model Data */
	    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	    std::vector<Mesh> meshes;
	    std::string directory;
	    bool gammaCorrection;

	    /*  Functions   */
	    // constructor, expects a filepath to a 3D model.
	    Model(void);
		Model ( Model const & src );
		virtual ~Model(void);
		static bool PreLoad(const std::string& key, std::string const &path, std::string const &shaderfile);
	    // draws the model, and thus all its meshes
	    void Draw(Camera *camera);

	private:
	    /*  Functions   */
	    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	    void loadModel(std::string const &path);

	    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	    void processNode(aiNode *node, const aiScene *scene);

	    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	    // checks all material textures of a given type and loads the textures if they're not loaded yet.
	    // the required info is returned as a Texture struct.
	    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};
#endif
