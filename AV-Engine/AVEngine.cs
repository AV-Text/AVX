using Blueprint.Blue;
using System.Text;

namespace AVXFramework
{
    public class AVEngine
    {
        private Blueprint.Blue.Blueprint BlueprintLib;
        private Pinshot.Blue.PinshotLib PinshotLib;
        private const string SDK = "C:/src/AVX/omega/AVX-Omega-3911.data";
        private NativeStatement SearchEngine;

        public AVEngine()
        {
            this.BlueprintLib = new();
            this.PinshotLib = new();

            this.SearchEngine = new NativeStatement(SDK);
        }
        public void Release()
        {
            this.SearchEngine.Release();
        }
        ~AVEngine()
        {
            this.Release();
        }
        public (QStatement? stmt, string error, string result) Execute(string command)
        {
            var pinshot = this.PinshotLib.Parse(command);
            if (pinshot.root != null)
            {
                if (string.IsNullOrWhiteSpace(pinshot.root.error))
                {
                    var blueprint = this.BlueprintLib.Create(pinshot.root);

                    if (blueprint != null)
                    {
                        if (blueprint.IsValid)
                        {
                            if (blueprint.Singleton != null)
                            {
                                ; // process singleton command
                                return (blueprint, "", "Pretend that this is the result of an executed Quelle command");
                            }
                            else if (blueprint.Commands != null)
                            {
                                var expression = blueprint.Commands.Searches.ToList();
//                              string yaml = ICommand.YamlSerializerRaw(expression);
                                string yaml = ICommand.JsonSerializerRaw(expression);

                                // CancellationToken++ code needs to be refactored with RapidJson (delete references to RapidYaml)
                                UInt16 span = blueprint.LocalSettings.Span.Value;
                                byte lexicon = (byte) (blueprint.LocalSettings.Lexicon.Value);
                                byte similarity = blueprint.LocalSettings.Similarity.Value;
                                bool fuzzyLemmata = blueprint.LocalSettings.Similarity.AutomaticLemmaMatching;

                                List<(byte book, byte chapter, byte verse)> scope = new();

                                if (this.SearchEngine.Search(yaml, span, lexicon, similarity, fuzzyLemmata, scope))
                                {
                                    return (blueprint, "", this.SearchEngine.Summary);
                                }

                                return (blueprint, "Search failed for unknown reason", "");
                            }
                            else
                            {
                                return (blueprint, "Internal Error: Unexpected blueprint encountered.", "");
                            }
                        }
                        else
                        {
                            if (blueprint.Errors.Count > 0)
                            {
                                var errors = string.Join("; ", blueprint.Errors);
                                return (blueprint, errors, "");
                            }
                            else
                            {
                                return (blueprint, "Blueprint was invalid, but the error list was empty.", "");
                            }
                        }
                    }
                    else
                    {
                        return (blueprint, "Blueprint was invalid (unexpected error).", "");
                    }
                }
                else
                {
                    return (null, pinshot.root.error, "");
                }
            }
            return (null, "Unable to parse the statement.", "");
        }
    }
}