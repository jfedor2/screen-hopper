const examples = [
    {
        'description': '16:10 screen side to side with a 3:2 screen',
        'config':
        {
            "version": 4,
            "unmapped_passthrough": true,
            "partial_scroll_timeout": 1000000,
            "interval_override": 0,
            "constraint_mode": 2,
            "offscreen_sensitivity": 4000,
            "screens": [
                {
                    "x": 0,
                    "y": 0,
                    "w": 14400000,
                    "h": 9000000,
                    "sensitivity": 8000
                },
                {
                    "x": 14400000,
                    "y": 0,
                    "w": 13500000,
                    "h": 9000000,
                    "sensitivity": 8000
                }
            ],
            "mappings": [
            ]
        }
    },
    {
        'description': 'two 16:9 screens, one on top of the other',
        'config':
        {
            "version": 4,
            "unmapped_passthrough": true,
            "partial_scroll_timeout": 1000000,
            "interval_override": 0,
            "constraint_mode": 2,
            "offscreen_sensitivity": 4000,
            "screens": [
                {
                    "x": 0,
                    "y": 0,
                    "w": 16000000,
                    "h": 9000000,
                    "sensitivity": 4000
                },
                {
                    "x": 0,
                    "y": 9000000,
                    "w": 16000000,
                    "h": 9000000,
                    "sensitivity": 4000
                }
            ],
            "mappings": [
            ]
        }
    },
];

export default examples;
