namespace NflMatchPredictor
{
    class NFL
    {
        static void Main()
        {
            // Input team stats
            Console.Write("Enter the name of the home team: ");
            string? homeTeam = Console.ReadLine();
            Console.Write("Enter the home team's wins: ");
            int homeTeamWins = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the home team's losses: ");
            int homeTeamLosses = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the home team's ties: ");
            int homeTeamTies = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the home team's points scored: ");
            double homeTeamPointsScored = Convert.ToDouble(Console.ReadLine());
            Console.Write("Enter the home team's points allowed: ");
            double homeTeamPointsAllowed = Convert.ToDouble(Console.ReadLine());
            Console.Write("Enter the home team's defensive ranking: ");
            int homeTeamDefRank = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter how many non-star starters are injuried / not playing: ");
            int homeTeamNotPlaying = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter how many star starters are injuried / not playing: ");
            int homeTeamStarNotPlaying = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine();

            Console.Write("Enter the name of the away team: ");
            string? awayTeam = Console.ReadLine();
            Console.Write("Enter the away team's wins: ");
            int awayTeamWins = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the away team's losses: ");
            int awayTeamLosses = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the away team's ties: ");
            int awayTeamTies = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the away team's points scored per game: ");
            double awayTeamPointsScored = Convert.ToDouble(Console.ReadLine());
            Console.Write("Enter the away team's points allowed per game: ");
            double awayTeamPointsAllowed = Convert.ToDouble(Console.ReadLine());
            Console.Write("Enter the away team's defensive ranking: ");
            int awayTeamDefRank = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter how many non-star starters are injuried / not playing: ");
            int awayTeamNotPlaying = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter how many star starters are injuried / not playing: ");
            int awayTeamStarNotPlaying = Convert.ToInt32(Console.ReadLine());
            Console.Write("Are they playing TNF games: ");
            bool TNFAway = Convert.ToBoolean(Console.ReadLine());
            Console.WriteLine();

            // Calculate average PPG and PAPG
            double homeTeamAvgPPG = (homeTeamPointsScored / (homeTeamWins + homeTeamLosses + homeTeamTies));
            double homeTeamAvgPAPG = (homeTeamPointsAllowed / (homeTeamWins + homeTeamLosses + homeTeamTies));

            double awayTeamAvgPPG = (awayTeamPointsScored / (awayTeamWins + awayTeamLosses + awayTeamTies));
            double awayTeamAvgPAPG = (awayTeamPointsAllowed / (awayTeamWins + awayTeamLosses + awayTeamTies));

            // Calculate Defense effect
            if (homeTeamDefRank <= 10)
            {
                homeTeamAvgPAPG -= 6;
            }
            else if (homeTeamDefRank <= 20 && homeTeamDefRank > 10)
            {
                homeTeamAvgPAPG += 3;
            }
            else
            {
                homeTeamAvgPAPG += 6;
            }

            if (awayTeamDefRank <= 10)
            {
                awayTeamAvgPAPG -= 6;
            }
            else if (awayTeamDefRank <= 20 && awayTeamDefRank > 10)
            {
                awayTeamAvgPAPG += 3;
            }
            else
            {
                awayTeamAvgPAPG += 6;
            }

            // Calculate Home team non-star injuries
            if (homeTeamNotPlaying == 0)
            {
                homeTeamAvgPPG += 0;
            }
            else if (homeTeamNotPlaying == 1)
            {
                homeTeamAvgPPG -= 1.5;
            }
            else
            {
                homeTeamAvgPPG -= 3;
            }

            // Calculate Home team star injuries
            if (homeTeamStarNotPlaying == 0)
            {
                homeTeamAvgPPG += 0;
            }
            else if (homeTeamStarNotPlaying == 1)
            {
                homeTeamAvgPPG -= 3.5;
            }
            else
            {
                homeTeamAvgPPG -= 7;
            }

            // Calculate Away team non-star injuries
            if (awayTeamNotPlaying == 0)
            {
                awayTeamAvgPPG += 0;
            }
            else if (awayTeamNotPlaying == 1)
            {
                awayTeamAvgPPG -= 1.5;
            }
            else
            {
                awayTeamAvgPPG -= 3;
            }

            // Calculate Away team star injuries
            if (awayTeamStarNotPlaying == 0)
            {
                awayTeamAvgPPG += 0;
            }
            else if (awayTeamStarNotPlaying == 1)
            {
                awayTeamAvgPPG -= 3.5;
            }
            else
            {
                awayTeamAvgPPG -= 7;
            }

            // Calculate Thursday night
            if (TNFAway == true)
            {
                awayTeamAvgPPG -= 3.5;
            }
            else if (TNFAway == false)
            {
                awayTeamAvgPPG += 0;
            }

            // Calculate expected scores
            int homeAdvantage = 2;
            double homeTeamExpectedScore = ((homeTeamAvgPPG + awayTeamAvgPAPG) / 2) + homeAdvantage;
            double awayTeamExpectedScore = ((awayTeamAvgPPG + homeTeamAvgPAPG) / 2);

            // Determine winner and spread of victory
            string? winner;
            double spread;
            double combinedScore = homeTeamExpectedScore + awayTeamExpectedScore;
            if (homeTeamExpectedScore > awayTeamExpectedScore)
            {
                winner = homeTeam;
                spread = (homeTeamExpectedScore - awayTeamExpectedScore);
            }
            else
            {
                winner = awayTeam;
                spread = (awayTeamExpectedScore - homeTeamExpectedScore);
            }

            // Output winner, final score, and spread of victory
            Console.WriteLine($"{winner} wins with a final score of {awayTeamExpectedScore:0.00}-{homeTeamExpectedScore:0.00} and a spread of {spread:0.00} points and a combined score of {combinedScore:0.00}.");
        }
    }
}


